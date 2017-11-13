#include "omxplayer.h"

M_OMXPlayer::M_OMXPlayer(QObject *parent) :
    IMoviePlayer(parent),
    state(IMoviePlayer::PLAYER_STATE_IDLE),
    playing_Type(IMoviePlayer::PLAYING_NOTHING)
{
    playerProgramPath = settings.value("movies/omxplayer/program_path", "/usr/bin/omxplayer").toString();

    if (!QFile::exists(playerProgramPath)) {
        state = IMoviePlayer::PLAYER_STATE_ERROR;
        Log::error("Cannot find omxplayer at path: " + playerProgramPath);
        return;
    }

    playerArgs = settings.value("movies/omxplayer/program_args", "-o hdmi").toString().split(' ');

    youtube_dlProgramPath = settings.value("movies/youtube_dl/program_path", "/usr/bin/youtube-dl").toString();

    if (!QFile::exists(youtube_dlProgramPath)) {
        state = IMoviePlayer::PLAYER_STATE_ERROR;
        Log::error("Cannot find youtube-dl at path: " + youtube_dlProgramPath);
        return;
    }

    currentIndex = -1;

    connect(&playerProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(playerErrorHandler(QProcess::ProcessError)));
    connect(&playerProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(playerFinishedHandler(int,QProcess::ExitStatus)));
    connect(&playerProcess, SIGNAL(started()), this, SLOT(playerStartedHandler()));

    connect(&playerProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadOMXStdOut()));
    connect(&youtube_dl, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStdOut()));
    connect(&youtube_dl, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(youtube_dlFinishedHandler(int,QProcess::ExitStatus)));
}

M_OMXPlayer::~M_OMXPlayer() {
    if (playerProcess.state() == QProcess::Running) {
        playerProcess.terminate();
        if (!playerProcess.waitForFinished(settings.value("movies/omxplayer/terminate_timeout", 3000).toUInt())) {
          Log::omx("omxplayer destructor terminating timeout. Killing...");
            playerProcess.kill();
        }
    }

}

void M_OMXPlayer::deletePlaylist()
{
 stop();
 playlist.clear();
 currentIndex = -1; 
}

Track M_OMXPlayer::getCurrentTrack()
{
  Track returnTrack;
  if(currentIndex > -1)
    returnTrack = playlist.at(currentIndex);

  return returnTrack;
}

void M_OMXPlayer::play(const QString &filename)
{
  Log::info(Q_FUNC_INFO);
    if (!QFile::exists(filename)) 
    {
        Log::omx("Movie file does not exists:" + filename);
        return;
    }

    if (state == IMoviePlayer::PLAYER_STATE_PLAYING || state == IMoviePlayer::PLAYER_STATE_PAUSED) {
        stop();
    }

    QStringList playerArgsList;
    playerArgsList << "-b" << "-t" << "1" << playerArgs << filename;
    currentMovieFilePath = filename;

    Log::omx("omxplayer starting playing file:" + filename);

    playing_Type = IMoviePlayer::PLAYING_MOVIE;
    sig_PlayingMovie();
    playerProcess.start(playerProgramPath, playerArgsList);
}

void M_OMXPlayer::playYoutube(const QString url) 
{
  Log::info(Q_FUNC_INFO);

  if (state == IMoviePlayer::PLAYER_STATE_PLAYING || state == IMoviePlayer::PLAYER_STATE_PAUSED) 
  {
        stop();
    }
  QStringList youtube_dlArgsList;
  youtube_dlArgsList << "-g" << "-f" << "best" << url;
  youtube_dl.start(youtube_dlProgramPath, youtube_dlArgsList);

/*
  if (state == IMoviePlayer::PLAYER_STATE_PLAYING || state == IMoviePlayer::PLAYER_STATE_PAUSED) {
        stop();
    }


    QString str = "`youtube-dl -g " + url + "`";
    str = str.toLatin1();
    QStringList playerArgsList;
    playerArgsList << "-b" << playerArgs << url;

    Log::omx("omxplayer starting playing file:" + url);

    playing_Type = IMoviePlayer::PLAYING_MOVIE;
    sig_PlayingMovie();
    //playerProcess.start(playerProgramPath, playerArgsList);
    playerProcess.start("/usr/bin/omxplayer -b -o local \\`/usr/bin/youtube-dl\\ -g\\ " + url + "\\`");
    */
}

void M_OMXPlayer::play(int index)
{
    if(index < playlist.size())
    {
      track = playlist.at(index);
      track.playlistPos = QString("%1").arg(index);
      currentIndex = index;
      QString filename = playlist.at(index).path;

      if (!QFile::exists(filename))
      {
          Log::omx("Movie file does not exists:" + filename);
          return;
      }

      if (state == IMoviePlayer::PLAYER_STATE_PLAYING || state == IMoviePlayer::PLAYER_STATE_PAUSED) {
          stop();
      }

      QStringList playerArgsList;
      playerArgsList << playerArgs << filename;
      currentMovieFilePath = filename;

      Log::omx("omxplayer starting playing file:" + filename);

      playing_Type = IMoviePlayer::PLAYING_MUSIC;
      playerProcess.start(playerProgramPath, playerArgsList);

   }
}

void M_OMXPlayer::playStream(const QString &stream)
{

    if (state == IMoviePlayer::PLAYER_STATE_PLAYING || state == IMoviePlayer::PLAYER_STATE_PAUSED) 
    {
        stop();
    }

    QStringList playerArgsList;
    playerArgsList << "--live" << "-b" << playerArgs << stream;
    currentMovieFilePath = stream;

    Log::omx("omxplayer startet: " + stream);

    playing_Type = IMoviePlayer::PLAYING_STREAM;
    playerProcess.start(playerProgramPath, playerArgsList);
}

void M_OMXPlayer::pause() 
{
    if (state == IMoviePlayer::PLAYER_STATE_PLAYING) 
    {
        setState(IMoviePlayer::PLAYER_STATE_PAUSED);
        Log::omx("Pausing omxplayer movie:" + currentMovieFilePath);
        Log::omx("omxplayer state = PLAYER_STATE_PAUSE");
        playerProcess.write("p");
    }
}

void M_OMXPlayer::resume() 
{
    if (state == IMoviePlayer::PLAYER_STATE_PAUSED) 
    {
        setState(IMoviePlayer::PLAYER_STATE_PLAYING);
        playerProcess.write("p");
        Log::omx("omxplayer state = PLAYER_STATE_PLAYING");
        Log::omx("Resuming omxplayer movie:" + currentMovieFilePath);
    }
}

void M_OMXPlayer::stop() 
{
    //setState(IMoviePlayer::PLAYER_STATE_IDLE);

    if (playerProcess.state() != QProcess::Running) {
        Log::omx("Player ins not running" );
        return;
    }

    //qDebug() << "Stopping omxplayer movie:" << currentMovieFilePath;
    Log::omx("omxplayer stoppe " + currentMovieFilePath);
    playerProcess.write("q");

    if (!playerProcess.waitForFinished(settings.value("movies/omxplayer/stop_timeout", 1000).toUInt())) 
    {
        Log::omx("omxplayer stopping timeout. Terminating...");
        playerProcess.terminate();
        if (!playerProcess.waitForFinished(settings.value("movies/omxplayer/stop_terminate_timeout", 2000).toUInt())) 
        {
            Log::omx("omxplayer terminate timeout. Killing...");
            playerProcess.kill();
        }
    }

}

void M_OMXPlayer::sendCmd(quint8 cmd, quint8 value) {
    if (state != IMoviePlayer::PLAYER_STATE_PLAYING)
        return;

    switch (cmd) {
    case IMoviePlayer::PLAYER_CMD_SET_FRAMEDROP:
        break;
    case IMoviePlayer::PLAYER_CMD_SET_SUBTITLES:
        playerProcess.write("s");
        break;
    }
}

void M_OMXPlayer::youtube_dlFinishedHandler(int exitCode, QProcess::ExitStatus exitStatus) 
{
    Log::omx("youtube-dl finished. Returned: " + QString("%1").arg(exitCode) 
              + "; exit status: " + QString("%1").arg(exitStatus));

}
void M_OMXPlayer::playerFinishedHandler(int exitCode, QProcess::ExitStatus exitStatus) 
{
    Log::omx("omxplayer finished. Returned: " + QString("%1").arg(exitCode) 
              + "; exit status: " + QString("%1").arg(exitStatus));

    setState(IMoviePlayer::PLAYER_STATE_IDLE);
    Log::omx("omxplayer state = PLAYER_STATE_IDLE");
    if(playing_Type == IMoviePlayer::PLAYING_MUSIC && exitCode == 0)
    {
      play(currentIndex + 1);
    }
//    emit sig_PlayerFinished(currentMovieFilePath);
}

void M_OMXPlayer::playerErrorHandler(QProcess::ProcessError error) 
{
  Log::error("omxplayer process error " + error);

    state = IMoviePlayer::PLAYER_STATE_ERROR;
    Log::omx("omxplayer state = PLAYER_STATE_ERROR");

}

void M_OMXPlayer::playerStartedHandler() 
{
    Log::omx("omxplayer started");
    Log::omx("omxplayer state = PLAYER_STATE_PLAYING");

    if(playing_Type == IMoviePlayer::PLAYING_MUSIC)
    {
      //connected with Socket::onPlayingTrack(Track)
      sig_PlayingTrack(track);

      state = (IMoviePlayer::PLAYER_STATE_PLAYING);
    }
    else
    {
      setState(IMoviePlayer::PLAYER_STATE_PLAYING);
      QTimer::singleShot(500, this, SLOT(setPlayed()));
    }
  /*if(state == IMoviePlayer::PLAYER_STATE_PLAYING &&
     playing_Type == IMoviePlayer::PLAYING_MOVIE)
  {
    sig_SetPlayed(currentMovieFilePath);
  }*/
}

void M_OMXPlayer::setPlayed()
{
    sig_SetPlayed(currentMovieFilePath);
}
void M_OMXPlayer::sendCommand(QString cmd)
{
  if(state != IMoviePlayer::PLAYER_STATE_PLAYING)
    return;
//  const char* command = cmd.toAscii();
  playerProcess.write(cmd.toLatin1());
}

void M_OMXPlayer::setState(quint8 s)
{
  state = s;
  sig_NewState(state);
}

void M_OMXPlayer::setFavorite()
{
  if(currentIndex < 0 || currentIndex > playlist.size())
    return;
   Track track = playlist.at(currentIndex);
  if(track.favorite == "1") 
     playlist[currentIndex].favorite = "0";
  else
     playlist[currentIndex].favorite = "1";
}

void M_OMXPlayer::updateID3Tag_Title(QString oldTitle, QString newTitle)
{
  Track tr;
  for(int i = 0; i < playlist.size(); i++)
  {
    tr = playlist.at(i);
    if(tr.title == oldTitle)
       playlist[i].title = newTitle;
  }
}

void M_OMXPlayer::updateID3Tag_Album(QString oldAlbum, QString newAlbum)
{
  Track tr;
  for(int i = 0; i < playlist.size(); i++)
  {
    tr = playlist.at(i);
    if(tr.album == oldAlbum)
       playlist[i].album = newAlbum;
  }
}

void M_OMXPlayer::updateID3Tag_Artist(QString oldArtist, QString newArtist)
{
  Track tr;
  for(int i = 0; i < playlist.size(); i++)
  {
    tr = playlist.at(i);
    if(tr.artist == oldArtist)
       playlist[i].artist = newArtist;
  }
}

void M_OMXPlayer::readyReadStdOut()
{
  Log::omx(Q_FUNC_INFO);
  QString url = youtube_dl.readAllStandardOutput();
  Log::omx(url);

    playing_Type = IMoviePlayer::PLAYING_STREAM;
    playerProcess.start("/usr/bin/omxplayer -o hdmi -b " + url + " > /tmp/omx.log" );
}


void M_OMXPlayer::readyReadOMXStdOut()
{
//  Log::omx(Q_FUNC_INFO);
  QString url = playerProcess.readAllStandardOutput();
  Log::omx(url);
}
