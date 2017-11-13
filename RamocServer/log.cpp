#include "log.h"

Log::Log(QObject *parent) : QObject(parent)
{
}

void Log::info(QString str)
{
  //green
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "INFO \033[32;1m" << str <<"\033[0m";
}

void Log::error(QString str)
{
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "ERROR\033[31;1m" << str <<"\033[0m";
}

void Log::db(QString str)
{
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "DB   \033[34;1m" << str <<"\033[0m";
}

void Log::omx(QString str)
{
  //purpel
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "OMX   \033[35;1m" << str <<"\033[0m";
}

void Log::tcp(QString str)
{
  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "TCP   \033[36;1m" << str <<"\033[0m";
}

