#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QStringList>
#include <QPixmap>

#include "log.h"

#include "omxplayer.h"
#include "socket.h"
#include "database.h"
//#include "music/musicPlayer.h"

class Server : public QObject
{
  Q_OBJECT

  private:
  QString ipAddress;
  QTcpServer* tcpServer;

  Socket* socket;
  DataBase* database;
  M_OMXPlayer* player;
//  MusicPlayer* musicPlayer;

  public:
  Server( M_OMXPlayer* p, DataBase* db, QObject *parent = 0);
  QString getIP() { return ipAddress; }

signals:
  void sig_NewChannelIcon(QPixmap);
  void sig_InsertMovies();
  //void sig_SetPlayed(QString);
  void sig_PlayedSet();
  void sig_GetUnsortedFiles();
  void sig_SendUnsortedFiles(QString);
  void sig_InsertMovie(QString, QString);

//  void sig_InsertMovie(QString, QString);

  public slots:
  void onNewConnection();
  void onDisconnected();
};

#endif // SERVER_H
