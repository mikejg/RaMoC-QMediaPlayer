#include "server.h"

Server::Server(M_OMXPlayer* p, DataBase* db, QObject *parent) : QObject(parent)
{
  Log::info("Starte Server Konstruktor");
  player    = p;
  database  = db;
  tcpServer = new QTcpServer(this);

  if (!tcpServer->listen(QHostAddress::Any, 4444))
    Log::error("Server " + tcpServer->errorString());

  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
  // use the first non-localhost IPv4 address
  for (int i = 0; i < ipAddressesList.size(); ++i)
  {
    if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
    {
      ipAddress = ipAddressesList.at(i).toString();
      break;
    }
  }

  // if we did not find one, use IPv4 localhost
  if (ipAddress.isEmpty())
  ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
  Log::info("Ende Server Konstruktor");
}

void Server::onNewConnection()
{
  socket = new Socket(tcpServer->nextPendingConnection(), player, database, this);
  Log::info("Server wurde mit " + socket->peerAddress() +" verbunden");

  connect(this, SIGNAL(sig_PlayedSet()), socket, SLOT(onPlayedSet()));
  connect(this, SIGNAL(sig_SendUnsortedFiles(QString)), socket, SLOT(onUnsortedFiles(QString)));

  connect(socket, SIGNAL(sig_Disconnected()), this, SLOT(onDisconnected()));
  connect(socket, SIGNAL(sig_InsertMovies()), this, SIGNAL(sig_InsertMovies()));
  //connect(socket, SIGNAL(sig_SetPlayed(QString)), this, SIGNAL(sig_SetPlayed(QString)));
  connect(socket, SIGNAL(sig_GetUnsortedFiles()), this, SIGNAL(sig_GetUnsortedFiles()));
  connect(socket, SIGNAL(sig_InsertMovie(QString, QString)), this, SIGNAL(sig_InsertMovie(QString, QString)));
  connect(socket, SIGNAL(sig_NewChannelIcon(QPixmap)),  this, SIGNAL(sig_NewChannelIcon(QPixmap)));
}

void Server::onDisconnected()
{
  sender()->deleteLater();
}
