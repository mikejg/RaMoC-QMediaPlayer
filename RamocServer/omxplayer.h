#ifndef OMXPLAYERMOVIEPLAYER_H
#define OMXPLAYERMOVIEPLAYER_H

#include <QObject>
#include <QProcess>
#include <QSettings>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QTimer>
#include "imoviemplayer.h"
#include "log.h"
#include "database.h"

class M_OMXPlayer : public IMoviePlayer
{
    Q_OBJECT

private:
    quint8 state;
    quint8 playing_Type;

    QSettings settings;
    QString playerProgramPath;
    QStringList playerArgs;

    QString youtube_dlProgramPath;
    QStringList youtube_dlArgs;

    QProcess playerProcess;
    QProcess youtube_dl;
    QString currentMovieFilePath;
    
    QList<Track> playlist;
    
    Track track;
    int currentIndex;
    void setState(quint8 s);

public:
    explicit M_OMXPlayer(QObject *parent = 0);
    virtual ~M_OMXPlayer();
   
    void    appendTrack(Track tr) { playlist << tr; }
    QString currentPath() { return currentMovieFilePath; }
    void    deletePlaylist();
    int     getCurrentIndex() { return currentIndex; }
    Track   getCurrentTrack();
    QList<Track> getPlaylist() { return playlist; }
    void    play(int index);
    void    playYoutube(QString);
    quint8  playerState() { return state; }
    void    sendCommand(QString cmd);
    void    setFavorite();
    void    toggleSubtitle() { playerProcess.write("s"); }
    void    nextSubtitle() { playerProcess.write("m"); }
    void    prevSubtitle() { playerProcess.write("n"); }
    void    updateID3Tag_Title(QString oldTitle, QString newTitle);
    void    updateID3Tag_Album(QString oldAlbum, QString newAlbum);
    void    updateID3Tag_Artist(QString oldArtist, QString newArtist);
    
public slots:
    virtual void play(const QString &filename);
    virtual void playStream(const QString &stream);
    virtual void pause();
    virtual void resume();
    virtual void stop();
    virtual void sendCmd(quint8 cmd, quint8 value);
    void setPlayed();

signals:
    void sig_NewState(quint8 s);
    void sig_PlayingTrack(Track);
    void sig_PlayingMovie();
    void sig_SetPlayed(QString);

protected slots:
    void playerFinishedHandler(int exitCode, QProcess::ExitStatus exitStatus);
    void youtube_dlFinishedHandler(int exitCode, QProcess::ExitStatus exitStatus);
    void playerErrorHandler(QProcess::ProcessError error);
    void playerStartedHandler();
    void readyReadStdOut();
    void readyReadOMXStdOut();
};

#endif // OMXPLAYERMOVIEPLAYER_H
