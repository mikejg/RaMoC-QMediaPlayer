#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QStringList>
#include <QDebug>
#include <QSettings>
#include <QProcess>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QPixmap>
#include <QHostAddress>

#include "log.h"

#include "constants.h"
#include "omxplayer.h"
#include "database.h"
//#include "omxplayermovieplayer.h"
//
//#include "music/musicPlayer.h"
//
using namespace constants;

class Socket : public QObject
{
    Q_OBJECT

  private:
    QTcpSocket*   tcpSocket;
    M_OMXPlayer*  player;
    DataBase*     database;

    //QEventLoop loop;
    bool isWriting;
    QStringList tcpStringList;

    QString omxPlayer_currentPath;
    quint8 omxPlayer_state;
   
    QSettings* settings;
    QString string_NAS_IP;
    QString string_MAC_Adresse;
    QString string_Freigabe;
    QString string_Passwort;
    QString string_User;
    QString string_DataBase;
    QString string_TVHeadEndIP;
    QString string_TVHeadEndUser;
    QString string_TVHeadEndPassword;
//
//    QString stringExec;
//    QString string_Error;
//
//    QStringList stringList_Files;
//    QStringList stringList_NewMovies;
    QStringList stringList_FilesToDelete;
    QStringList stringList_ArtistAlben;
//
//    bool isMovie;
//    bool isTVShow;
  void handleArchiveMovie(QString);
  void handleArtistAlben(QString);
  void handleInsertAlbum(QString);
  void handleNextArtistAlben();
  void handleDeleteMovie(QString);
  void handleGetSettings();
  void handleInsertMovie(QString);
  void handleNewTVChannel(QString str);
  void handlePlay(QString str);
  void handlePlayTrack(QString str);
  void handleRestoreMovie(QString);
  void handleUnsortedFiles();
  void handleSendPlaylist();
  void handleRandom();
  void handleFavorite();
  void handleSetID3Tag(QString);
  void handleSetFavorite(QString);
  void handleSetSampler(QString);
  void handleSetTVHeadEnd(QString);
  void handleSetNAS(QString);
  void handlePlayYoutube(QString);
  //void writeData();

  QString genJsonTracks(QList<Track> tracklist);

public:
    explicit Socket(QTcpSocket* ts, M_OMXPlayer* p, DataBase* db, QObject *parent = 0);
    ~Socket();

    QString peerAddress() { return tcpSocket->peerAddress().toString(); }
    void writeData(QString string_Data, bool debug = false);
//    void check_PlayPause();
//    QString genJsonTracks(QList<Track>);
//    void getFavorite();
//    void getRandom();
//    void sendPlaylist();

signals:
    void sig_Disconnected();
    void sig_NewChannelIcon(QPixmap);
    void sig_InsertMovies();
    //void sig_SetPlayed(QString);
    void sig_GetUnsortedFiles();
    void sig_InsertMovie(QString, QString);

public slots:
    void onDisconnected();
    void onReadData();
    void onNewState(quint8);
    void onPlayedSet();
    void onPlayingTrack(Track);
    void onUnsortedFiles(QString);
//    void onBytesWritten(qint64);

//    void slot_disconnected();
//    void slot_playingTrack(Track);
//
//    //Testing
//    void playerStartedHandler(QString);
//    void playerPausedHandler(QString);
//    void playerResumedHandler(QString);
//    void playerFinishedHandler(QString);
};

#endif // SOCKET_H

