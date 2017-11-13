#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QLabel>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include "log.h"
#include "server.h"
#include "omxplayer.h"
#include "insertMovies.h"
#include "database.h"
#include "m_lastfm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QLabel* label_ChannelIcon;
    QDesktopWidget* desktop;
    QStringList stringList_Trailer;
    QProcess* process_TrailerDL; 
    QPixmap pixmap_Music;
    QPixmap pixmap_Main;

    M_OMXPlayer*  player;
    Server*       server;
    DataBase* database;  
    InsertMovies* insertMovies; 
    M_LastFm* lastFm;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDesktop(QDesktopWidget *d);

public slots:
    void handleInsertMovies();
    void handleNewInfo(QString str);
    void handleNewTrailer(QString str);
    void handleInsertMovies_Finished();
    void onNewChannelIcon(QPixmap);
    void onInsertMovie(QString, QString);
    void onPlayingTrack(Track);
    void trailer_Download_Finished(int, QProcess::ExitStatus);
    void onNewArtistPixmap(QPixmap);
    void onPlayingMovie();
};

#endif // MAINWINDOW_H
