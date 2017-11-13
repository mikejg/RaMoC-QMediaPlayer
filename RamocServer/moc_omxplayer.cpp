/****************************************************************************
** Meta object code from reading C++ file 'omxplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "omxplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'omxplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_M_OMXPlayer_t {
    QByteArrayData data[30];
    char stringdata0[353];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_M_OMXPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_M_OMXPlayer_t qt_meta_stringdata_M_OMXPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "M_OMXPlayer"
QT_MOC_LITERAL(1, 12, 12), // "sig_NewState"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 1), // "s"
QT_MOC_LITERAL(4, 28, 16), // "sig_PlayingTrack"
QT_MOC_LITERAL(5, 45, 5), // "Track"
QT_MOC_LITERAL(6, 51, 16), // "sig_PlayingMovie"
QT_MOC_LITERAL(7, 68, 13), // "sig_SetPlayed"
QT_MOC_LITERAL(8, 82, 4), // "play"
QT_MOC_LITERAL(9, 87, 8), // "filename"
QT_MOC_LITERAL(10, 96, 10), // "playStream"
QT_MOC_LITERAL(11, 107, 6), // "stream"
QT_MOC_LITERAL(12, 114, 5), // "pause"
QT_MOC_LITERAL(13, 120, 6), // "resume"
QT_MOC_LITERAL(14, 127, 4), // "stop"
QT_MOC_LITERAL(15, 132, 7), // "sendCmd"
QT_MOC_LITERAL(16, 140, 3), // "cmd"
QT_MOC_LITERAL(17, 144, 5), // "value"
QT_MOC_LITERAL(18, 150, 9), // "setPlayed"
QT_MOC_LITERAL(19, 160, 21), // "playerFinishedHandler"
QT_MOC_LITERAL(20, 182, 8), // "exitCode"
QT_MOC_LITERAL(21, 191, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(22, 212, 10), // "exitStatus"
QT_MOC_LITERAL(23, 223, 25), // "youtube_dlFinishedHandler"
QT_MOC_LITERAL(24, 249, 18), // "playerErrorHandler"
QT_MOC_LITERAL(25, 268, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(26, 291, 5), // "error"
QT_MOC_LITERAL(27, 297, 20), // "playerStartedHandler"
QT_MOC_LITERAL(28, 318, 15), // "readyReadStdOut"
QT_MOC_LITERAL(29, 334, 18) // "readyReadOMXStdOut"

    },
    "M_OMXPlayer\0sig_NewState\0\0s\0"
    "sig_PlayingTrack\0Track\0sig_PlayingMovie\0"
    "sig_SetPlayed\0play\0filename\0playStream\0"
    "stream\0pause\0resume\0stop\0sendCmd\0cmd\0"
    "value\0setPlayed\0playerFinishedHandler\0"
    "exitCode\0QProcess::ExitStatus\0exitStatus\0"
    "youtube_dlFinishedHandler\0playerErrorHandler\0"
    "QProcess::ProcessError\0error\0"
    "playerStartedHandler\0readyReadStdOut\0"
    "readyReadOMXStdOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_M_OMXPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       6,    0,  105,    2, 0x06 /* Public */,
       7,    1,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  109,    2, 0x0a /* Public */,
      10,    1,  112,    2, 0x0a /* Public */,
      12,    0,  115,    2, 0x0a /* Public */,
      13,    0,  116,    2, 0x0a /* Public */,
      14,    0,  117,    2, 0x0a /* Public */,
      15,    2,  118,    2, 0x0a /* Public */,
      18,    0,  123,    2, 0x0a /* Public */,
      19,    2,  124,    2, 0x09 /* Protected */,
      23,    2,  129,    2, 0x09 /* Protected */,
      24,    1,  134,    2, 0x09 /* Protected */,
      27,    0,  137,    2, 0x09 /* Protected */,
      28,    0,  138,    2, 0x09 /* Protected */,
      29,    0,  139,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 21,   20,   22,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 21,   20,   22,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void M_OMXPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        M_OMXPlayer *_t = static_cast<M_OMXPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_NewState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->sig_PlayingTrack((*reinterpret_cast< Track(*)>(_a[1]))); break;
        case 2: _t->sig_PlayingMovie(); break;
        case 3: _t->sig_SetPlayed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->play((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->playStream((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->pause(); break;
        case 7: _t->resume(); break;
        case 8: _t->stop(); break;
        case 9: _t->sendCmd((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 10: _t->setPlayed(); break;
        case 11: _t->playerFinishedHandler((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 12: _t->youtube_dlFinishedHandler((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 13: _t->playerErrorHandler((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 14: _t->playerStartedHandler(); break;
        case 15: _t->readyReadStdOut(); break;
        case 16: _t->readyReadOMXStdOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (M_OMXPlayer::*_t)(quint8 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&M_OMXPlayer::sig_NewState)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (M_OMXPlayer::*_t)(Track );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&M_OMXPlayer::sig_PlayingTrack)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (M_OMXPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&M_OMXPlayer::sig_PlayingMovie)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (M_OMXPlayer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&M_OMXPlayer::sig_SetPlayed)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject M_OMXPlayer::staticMetaObject = {
    { &IMoviePlayer::staticMetaObject, qt_meta_stringdata_M_OMXPlayer.data,
      qt_meta_data_M_OMXPlayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *M_OMXPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *M_OMXPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_M_OMXPlayer.stringdata0))
        return static_cast<void*>(const_cast< M_OMXPlayer*>(this));
    return IMoviePlayer::qt_metacast(_clname);
}

int M_OMXPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IMoviePlayer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void M_OMXPlayer::sig_NewState(quint8 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void M_OMXPlayer::sig_PlayingTrack(Track _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void M_OMXPlayer::sig_PlayingMovie()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void M_OMXPlayer::sig_SetPlayed(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
