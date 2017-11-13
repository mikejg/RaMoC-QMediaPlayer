#include "socket.h"

Socket::Socket(QTcpSocket* ts, M_OMXPlayer* p, DataBase* db, QObject* parent) : QObject(parent)
{
  tcpSocket = ts;
  player    = p;
  database  = db;
  
  isWriting = false;

  settings = new QSettings("RaMoC", "server");
  string_NAS_IP             = settings->value("NAS_IP", " ").toString();
  string_Freigabe           = settings->value("Freigabe", " ").toString();
  string_User               = settings->value("User", " ").toString();
  string_Passwort           = settings->value("Passwort", " ").toString();
  string_DataBase           = settings->value("mysql_IP", "localhost").toString();
  string_MAC_Adresse        = settings->value("MAC_Adresse", " ").toString();
  string_TVHeadEndIP        = settings->value("TVHeadEndIP", " ").toString();
  string_TVHeadEndUser      = settings->value("TVHeadEndUser", " ").toString();
  string_TVHeadEndPassword  = settings->value("TVHeadEndPassword", " ").toString();

  connect(tcpSocket, SIGNAL(disconnected()),  this, SLOT(onDisconnected()));
  connect(tcpSocket, SIGNAL(readyRead()),     this, SLOT(onReadData()));
  //connect(tcpSocket, SIGNAL(bytesWritten()),  &loop, SLOT(quit()));
//  connect(tcpSocket, SIGNAL(bytesWritten(qint64)),  this, SLOT(onBytesWritten(qint64)));

  connect(player, SIGNAL(sig_NewState(quint8)), this, SLOT(onNewState(quint8)));
  connect(player, SIGNAL(sig_PlayingTrack(Track)), this, SLOT(onPlayingTrack(Track)));
}

Socket::~Socket()
{
  //trenne alle Signal Slot Verbindungen
  tcpSocket->disconnect();

  tcpSocket->disconnectFromHost();
}

void Socket::onDisconnected()
{
  Log::tcp("Verbindung mit " + peerAddress() + " wurde getrennte");
  sig_Disconnected();
}

void Socket::handleArchiveMovie(QString str)
{
  str = str.remove("\n");
  QStringList strList_split = str.split("|");
  QString ramocId = strList_split.at(1);
  database->setArchive(ramocId);
}

void Socket::handleArtistAlben(QString str)
{
  str = str.remove("\n");
  QStringList strList_split = str.split("|");

  if(strList_split.size() < 2)
    return;

   stringList_ArtistAlben = database->getArtistAlben(strList_split.at(1));

  if(!stringList_ArtistAlben.isEmpty())
  {
    writeData(ArtistAlben + "|"  + stringList_ArtistAlben.first());
    stringList_ArtistAlben.removeFirst();
  }
}

void Socket::handleRestoreMovie(QString str)
{
  str = str.remove("\n");
  QStringList strList_split = str.split("|");
  QString ramocId = strList_split.at(1);
  database->unsetArchive(ramocId);
}

void Socket::handleDeleteMovie(QString str)
{
  str = str.remove("\n");
  QStringList strList_split = str.split("|");
  QString ramocId = strList_split.at(1);
  stringList_FilesToDelete = database->getFiles(ramocId);
  database->deleteMovie(ramocId);
  foreach(QString fileName, stringList_FilesToDelete)
  {
     QFile file(fileName);
     if(!file.remove())
      Log::error("Fehler beim Loeschen von " + fileName);
  }
}


void Socket::handleNextArtistAlben()
{
  if(!stringList_ArtistAlben.isEmpty())
    {
      writeData(ArtistAlben + "|" + stringList_ArtistAlben.first());
      stringList_ArtistAlben.removeFirst();
    }
  else
  {
      writeData(endArtistAlben );
  }
}

void Socket::handleGetSettings()
{
    QString str_State = QString("%1").arg(player->playerState());
    QString str_Settings = "001|" +
                  string_NAS_IP + "|" +
                  string_Freigabe + "|" +
                  string_User + "|" +
                  string_Passwort + "|" +
                  string_DataBase + "|" +
                  string_MAC_Adresse + "|" +
                  string_TVHeadEndIP + "|" +
                  string_TVHeadEndUser + "|" +
                  string_TVHeadEndPassword + "|" +
                  str_State + "|";
    writeData(str_Settings, true);
}

void Socket::handleInsertAlbum(QString str)
{
  QString artist;
  QString album;
  QString jsonString;
  QList<Track> list_Track;

  str = str.remove("\n");
  QStringList strList_split = str.split("|");

  if(strList_split.size() == 3)
  {
    artist = strList_split.at(1);
    album = strList_split.at(2);
    list_Track = database->getTracks_Artist_Album(artist, album);

    jsonString = "[";
    foreach(Track track, list_Track)
    {
      player->appendTrack(track);
      jsonString = jsonString + 
                   "{\"id\":\"" + track.ramoc_ID + "\"," +
                   "\"album_id\":\"" + track.album_ID + "\"," +
                   "\"title\":\"" + track.title + "\"," +
                   "\"pfad\":\"" + track.path + "\"," +
                   "\"artist\":\"" + track.artist + "\"," +
                   "\"album\":\"" + track.album + "\"," +
                   "\"favorite\":\"" + track.favorite + "\"," +
                   "\"sampler\":\"" + track.sampler + "\"" +
                   "},"; 
    }
    //letztes Komma wegschneiden
    if(jsonString.length() > 1)
      jsonString = jsonString.left(jsonString.length() - 1);

    jsonString = jsonString + "]";
    writeData(newTracks +  "|" + jsonString);
  }
}

void Socket::handleNewTVChannel(QString str)
{
  str = str.remove(newTVChannel);
  str = str.remove("\n");

  QStringList stringList_Arguments = str.split("|");

  str = stringList_Arguments.at(2);
  str = "/var/www/html/SenderIcon/" + str + ".png";

  if(QFile::exists(str))
  {
    sig_NewChannelIcon(QPixmap(str));
  }

  str = stringList_Arguments.at(1);

  str = str.replace(" ", "\\ ");
  str = str.replace("&", "\\&");
  str = str.replace("'", "\\'");

  //player->stop();
  player->playStream(str);
}

void Socket::handlePlay(QString str)
{
      str = str.remove("\n");
      QStringList strList_split = str.split("|");

      if(strList_split.size() == 2)
      {
        omxPlayer_state = player->playerState();
        omxPlayer_currentPath = player->currentPath();

        if(omxPlayer_state == IMoviePlayer::PLAYER_STATE_PLAYING) 
        {
          player->pause();
          return;
        }

        if(omxPlayer_state == IMoviePlayer::PLAYER_STATE_IDLE) 
        {
          player->play(strList_split.at(1));
          //connected with DataBase::onSetPlayed
          //sig_SetPlayed(strList_split.at(1));
          return;
        }

        if(omxPlayer_state == IMoviePlayer::PLAYER_STATE_PAUSED)
        {
          player->resume();
          return;
        }
      }
}

void Socket::handleUnsortedFiles()
{
  //connectet with DataBase::onGetUnsortedFiles()
  sig_GetUnsortedFiles();
}

void Socket::handleInsertMovie(QString str)
{
  str = str.remove("\n");
  QStringList strList_split = str.split("|");
  QString file_path = strList_split.at(1);
  QString tmdbId = strList_split.at(2);
  QString title = strList_split.at(3);

  //connected with MainWindow::onInsertMovie(QString, QString);
  sig_InsertMovie(file_path, title);
}

void Socket::handlePlayTrack(QString str)
{
  str = str.remove("\n");
  QStringList strList_split = str.split("|");

  if(strList_split.size() == 2)
  {
    int tracknr = strList_split.at(1).toInt();
    player->play(tracknr);
    //schreibe zurück welcher Track gespielt wird
    //slot_playingTrack(tracknr);
  }
}

void Socket::handleRandom()
{
  Log::tcp(Q_FUNC_INFO);
      QList<Track> list_Track;
      QString jsonString;

        list_Track = database->getRandom();

        jsonString = "[";
        foreach(Track track, list_Track)
        {
          player->appendTrack(track);
          jsonString = jsonString + 
                       "{\"id\":\"" + track.ramoc_ID + "\"," +
                       "\"album_id\":\"" + track.album_ID + "\"," +
                       "\"title\":\"" + track.title + "\"," +
                       "\"pfad\":\"" + track.path + "\"," +
                       "\"artist\":\"" + track.artist + "\"," +
                       "\"album\":\"" + track.album + "\"," +
                       "\"favorite\":\"" + track.favorite + "\"," +
                       "\"sampler\":\"" + track.sampler + "\"" +
                       "},"; 
        }
        //letztes Komma wegschneiden
        if(jsonString.length() > 1)
          jsonString = jsonString.left(jsonString.length() - 1);

        jsonString = jsonString + "]";
        writeData(newTracks + "|" +  jsonString);
}

void Socket::handleFavorite()
{
      QList<Track> list_Track;
      QString jsonString;

        list_Track = database->getFavorite();
        qDebug() << "Favoriten: " << list_Track.size();

        jsonString = "[";
        foreach(Track track, list_Track)
        {
          player->appendTrack(track);
          jsonString = jsonString + 
                       "{\"id\":\"" + track.ramoc_ID + "\"," +
                       "\"album_id\":\"" + track.album_ID + "\"," +
                       "\"title\":\"" + track.title + "\"," +
                       "\"pfad\":\"" + track.path + "\"," +
                       "\"artist\":\"" + track.artist + "\"," +
                       "\"album\":\"" + track.album + "\"," +
                       "\"favorite\":\"" + track.favorite + "\"," +
                       "\"sampler\":\"" + track.sampler + "\"" +
                       "},"; 
        }
        //letztes Komma wegschneiden
        if(jsonString.length() > 1)
          jsonString = jsonString.left(jsonString.length() - 1);

        jsonString = jsonString + "]";
        //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << jsonString;
        writeData(newTracks + "|" +  jsonString);
//        musicPlayer->exportPlaylist();
}

void Socket::handleSetFavorite(QString str)
{
  str = str.remove("\n");
  QStringList strList_split = str.split("|");

  if(strList_split.size() == 2)
  {
    database->setFavorite(strList_split.at(1));
  }
}

void Socket::handleSetSampler(QString str)
{
  str = str.remove("\n");
  QStringList strList_split = str.split("|");

  if(strList_split.size() == 2)
  {
    database->setSampler(strList_split.at(1));
  }
}

void Socket::handleSetTVHeadEnd(QString str)
{
  str = str.remove(setTVHeadEnd + "|");
  str = str.remove("\n");
  str = str.remove(" ");

  QStringList arguments = str.split("|");
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " Set TVHeadEnd";
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " TVHeadEnd IP       : " << arguments.at(0);
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " TVHeadEnd User     : " << arguments.at(1);
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " TVHeadEnd Password : " << arguments.at(2);

  settings->setValue("TVHeadEndIP", arguments.at(0));
  settings->setValue("TVHeadEndUser", arguments.at(1));
  settings->setValue("TVHeadEndPassword", arguments.at(2));
}

void Socket::handleSetNAS(QString str)
{
  str = str.remove(setNAS);
  str = str.remove("\n");
  str = str.remove(" ");

  QStringList arguments = str.split("|");
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " Set NAS";
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " NAS IP         : " << arguments.at(1);
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " NAS MAC Adresse: " << arguments.at(5);
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " Freigabe       : " << arguments.at(2);
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << " User           : " << arguments.at(3);

  QString stringExec = "sudo mv /etc/auto.master /etc/auto.master-last";
  system(stringExec.toLatin1().data());
  stringExec = "sudo sh -c \"echo '/mnt /etc/auto.share --timeout=600 --ghost' >> /etc/auto.master\"";
  system(stringExec.toLatin1().data());

  stringExec = "sudo mv /etc/auto.share /etc/auto.share-last";
  system(stringExec.toLatin1().data());
  stringExec = "sudo sh -c \"echo 'smb -fstype=cifs,username="
              + arguments.at(3)
              + ",password="
              + arguments.at(4)
              + " ://"
              + arguments.at(1)
              + "/"
              + arguments.at(2)
              + "' >> /etc/auto.share\"";
  system(stringExec.toLatin1().data());

  stringExec = "sudo sh -c \"echo '" + arguments.at(1) + "' > /var/www/html/nas-settings\"";
  system(stringExec.toLatin1().data());

  stringExec = "sudo sh -c \"echo '" + arguments.at(5) + "' >> /var/www/html/nas-settings\"";
  system(stringExec.toLatin1().data());

  settings->setValue("NAS_IP", arguments.at(1));
  settings->setValue("Freigabe", arguments.at(2));
  settings->setValue("User", arguments.at(3));
  settings->setValue("Passwort", arguments.at(4));
  settings->setValue("MAC_Adresse", arguments.at(5));
}

void Socket::handleSetID3Tag(QString str)
{
  str = str.remove("\n");

  QStringList arguments = str.split("|");

  QString ramocID = arguments.at(1);
  QString title   = arguments.at(2);
  QString album   = arguments.at(3);
  QString artist  = arguments.at(4);

  Track track = database->getTrack(ramocID);

  if(title != track.title)
  {
    Log::info("Aendere Titel");
    database->updateTitle(track, title);
    player->updateID3Tag_Title(track.title, title);
  }

  if(album != track.album)
  {
    Log::info("Aendere Album");
   database->updateAlbum(track, album);
    player->updateID3Tag_Album(track.album, album);
  }

  if(artist != track.artist)
  {
    Log::info("Aendere Artist");
    database->updateArtist(track, artist);
    player->updateID3Tag_Artist(track.artist, artist);
  }
  
  writeData(finishID3Tag);

}

void Socket::handlePlayYoutube(QString str)
{
  Log::info(Q_FUNC_INFO);
      str = str.remove("\n");
      QStringList strList_split = str.split("|");

      if(strList_split.size() == 2)
      {
          player->playYoutube(strList_split.at(1));
      }
}

void Socket::onReadData()
{
  int len = tcpSocket->bytesAvailable();

  QDataStream in(tcpSocket);
  in.setVersion(QDataStream::Qt_4_0);

  char char_Input[len];
  in.readRawData ( char_Input, len );
  QString string = QString::fromUtf8(char_Input, len-1);
//  Log::tcp("Neue Daten: " + string);

  if(string.startsWith(getSettings))
    handleGetSettings();

  if(string.startsWith(stop))
    player->stop();

  if(string.startsWith(newTVChannel))
    handleNewTVChannel(string);

  if(string.startsWith(scannForNewFiles))
  {
    sig_InsertMovies();
  }

  if(string.startsWith(play))
    handlePlay(string);

  if(string.startsWith(unsortedFiles))
    handleUnsortedFiles();

  if(string.startsWith(insertMovie))
    handleInsertMovie(string);

  if(string.startsWith(archiveMovie))
    handleArchiveMovie(string);

  if(string.startsWith(restoreMovie))
    handleRestoreMovie(string);

  if(string.startsWith(minutesForward))
  {
    player->sendCommand("[[A");
  }

  if(string.startsWith(minutesBackward))
  {
    player->sendCommand("[[B");
  }

  if(string.startsWith(backward))
  {
    player->sendCommand("<");
  }

  if(string.startsWith(forward))
  {
    player->sendCommand(">");
  }
  
  if(string.startsWith(ArtistAlben))
    handleArtistAlben(string);

  if(string.startsWith(nextArtistAlben))
    handleNextArtistAlben();

  if(string.startsWith(insertAlbum))
    handleInsertAlbum(string);
  
  if(string.startsWith(playTrack))
    handlePlayTrack(string);

  if(string.startsWith(sendPlaylist))
    handleSendPlaylist();

  if(string.startsWith(getRandom))
    handleRandom();

  if(string.startsWith(getFavorite))
    handleFavorite();

  if(string.startsWith(setFavorite))
    handleSetFavorite(string);

  if(string.startsWith(deletePlaylist))
    player->deletePlaylist();

  if(string.startsWith(deleteMovie))
    handleDeleteMovie(string);

  if(string.startsWith(setSampler))
    handleSetSampler(string);

  if(string.startsWith("021"))
  {
    handleSetTVHeadEnd(string);
  }

  if(string.startsWith(setNAS))
  {
    handleSetNAS(string);
  }

  if(string.startsWith(toggleSubtitle))
  {
    player->toggleSubtitle();
  }

  if(string.startsWith(nextSubtitle))
  {
    player->nextSubtitle();
  }

  if(string.startsWith(prevSubtitle))
  {
    player->prevSubtitle();
  }

  if(string.startsWith(setID3Tag))
  {
    handleSetID3Tag(string);
  }

  if(string.startsWith(playYoutube))
  {
    Log::info("Neue Daten: " + string);
    handlePlayYoutube(string);
  }
}

void Socket::onNewState(quint8 s)
{
  writeData(newState + "|" + QString("%1").arg(s),true);
}

void Socket::onPlayedSet()
{
  writeData(playedSet, true);
}

void Socket::onPlayingTrack(Track track)
{
/*  
  QString albumCover = database->getAlbumCover(track.album_ID);
  writeData(playTrack + "|" +
            track.playlistPos +
            "|" +
            albumCover, true);
*/   
  writeData(playTrack + "|" +
            track.playlistPos, true);

  database->setPlayed(track);
}

void Socket::onUnsortedFiles(QString str)
{
  writeData(unsortedFiles + "|" + str, true);
}

void Socket::writeData(QString string_Data, bool debug)
{
  string_Data = string_Data + "\n";
  if(debug)
    Log::tcp("Sende: " + string_Data);

    tcpSocket->write(string_Data.toUtf8());

}

void Socket::handleSendPlaylist()
{
  QList<Track> playlist = player->getPlaylist();
  QString jsonString = genJsonTracks(playlist);
  //QString coverString = "";

  int currentIndex = player->getCurrentIndex();
  if(currentIndex > -1)
  {
    Track track = player->getCurrentTrack();
    //coverString = database->getAlbumCover(track.album_ID);
  }
  writeData(sendPlaylist + "|" + jsonString 
            + "|" + QString("%1").arg(currentIndex));
}
/*
void Socket::writeData()
{
  QString string_Data;
  QByteArray byteArray;

  if(!isWriting && !tcpStringList.isEmpty())
  {
    isWriting = true;
    string_Data = tcpStringList.takeFirst();
    byteArray = string_Data.toUtf8();
    Log::tcp(QString("Bytes to write: %1").arg(byteArray.size()));
    tcpSocket->write(byteArray);
    //tcpSocket->waitForBytesWritten(5000);
  }
}

void Socket::onBytesWritten(qint64 bytes)
{
  Log::tcp(QString("Bytes written: %1").arg(bytes));
  isWriting = false;
  writeData();
  //QTimer::singleShot(100, this,SLOT(onTimeOut()));
}
*/

QString Socket::genJsonTracks(QList<Track> tracklist)
{
  QString jsonString;
  jsonString = "[";
  foreach(Track track, tracklist)
  {
    jsonString = jsonString +
                 "{\"id\":\"" + track.ramoc_ID + "\"," +
                 "\"album_id\":\"" + track.album_ID + "\"," +
                 "\"title\":\"" + track.title + "\"," +
                 "\"pfad\":\"" + track.path + "\"," +
                 "\"artist\":\"" + track.artist + "\"," +
                 "\"album\":\"" + track.album + "\"," +
                 "\"favorite\":\"" + track.favorite + "\"," +
                 "\"sampler\":\"" + track.sampler + "\"" +
                 "},";
  }
  //letztes Komma wegschneiden
  if(jsonString.length() > 1)
    jsonString = jsonString.left(jsonString.length() - 1);

  jsonString = jsonString + "]";
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << jsonString;
  return jsonString;
}
