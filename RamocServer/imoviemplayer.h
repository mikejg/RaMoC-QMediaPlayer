#ifndef IMOVIEMPLAYER_H
#define IMOVIEMPLAYER_H

#include <QObject>
#include <QString>

class IMoviePlayer : public QObject {
public:
    
    typedef enum {
                PLAYER_STATE_IDLE       =   0x00,
                PLAYER_STATE_PLAYING    =   0x01,
                PLAYER_STATE_PAUSED     =   0x02,
                PLAYER_STATE_ERROR      =   0xFF
    } MOVIE_PLAYER_STATE;
    
    typedef enum {
                PLAYER_CMD_SET_VOLUME       =   0x00,
                PLAYER_CMD_SET_SUBTITLES    =   0x01,
                PLAYER_CMD_SET_FRAMEDROP    =   0x02,
                PLAYER_CMD_10_SEC_FORWARD   =   0x03,
                PLAYER_CMD_10_SEC_BACKWARD  =   0x04
    } MOVIE_PLAYER_CMDS;
    
    typedef enum {
                PLAYING_NOTHING       =   0x00,
                PLAYING_MOVIE          =   0x01,
                PLAYING_STREAM          =   0x02,
                PLAYING_MUSIC          =   0x03,
    } PLAYING_TYPE;
    IMoviePlayer(QObject *parent = 0) : QObject(parent) {};
    
    virtual ~IMoviePlayer() {};
    
    virtual quint8 playerState() = 0;
    
public slots:
    
    virtual void play(const QString &filename) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
    virtual void sendCmd(quint8 cmd, quint8 value) = 0;
    
    
signals:
    void sig_PlayerStarted(QString filename);
    void sig_PlayerFinished(QString filename);
    void moviePlayPaused(QString filename);
    void moviePlayResumed(QString filename);
    
    
};

#endif // IMOVIEMPLAYER_H

