/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[15];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "handleInsertMovies"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "handleNewInfo"
QT_MOC_LITERAL(4, 45, 3), // "str"
QT_MOC_LITERAL(5, 49, 16), // "handleNewTrailer"
QT_MOC_LITERAL(6, 66, 27), // "handleInsertMovies_Finished"
QT_MOC_LITERAL(7, 94, 16), // "onNewChannelIcon"
QT_MOC_LITERAL(8, 111, 13), // "onInsertMovie"
QT_MOC_LITERAL(9, 125, 14), // "onPlayingTrack"
QT_MOC_LITERAL(10, 140, 5), // "Track"
QT_MOC_LITERAL(11, 146, 25), // "trailer_Download_Finished"
QT_MOC_LITERAL(12, 172, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(13, 193, 17), // "onNewArtistPixmap"
QT_MOC_LITERAL(14, 211, 14) // "onPlayingMovie"

    },
    "MainWindow\0handleInsertMovies\0\0"
    "handleNewInfo\0str\0handleNewTrailer\0"
    "handleInsertMovies_Finished\0"
    "onNewChannelIcon\0onInsertMovie\0"
    "onPlayingTrack\0Track\0trailer_Download_Finished\0"
    "QProcess::ExitStatus\0onNewArtistPixmap\0"
    "onPlayingMovie"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    1,   65,    2, 0x0a /* Public */,
       5,    1,   68,    2, 0x0a /* Public */,
       6,    0,   71,    2, 0x0a /* Public */,
       7,    1,   72,    2, 0x0a /* Public */,
       8,    2,   75,    2, 0x0a /* Public */,
       9,    1,   80,    2, 0x0a /* Public */,
      11,    2,   83,    2, 0x0a /* Public */,
      13,    1,   88,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,    2,    2,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleInsertMovies(); break;
        case 1: _t->handleNewInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->handleNewTrailer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->handleInsertMovies_Finished(); break;
        case 4: _t->onNewChannelIcon((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 5: _t->onInsertMovie((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->onPlayingTrack((*reinterpret_cast< Track(*)>(_a[1]))); break;
        case 7: _t->trailer_Download_Finished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 8: _t->onNewArtistPixmap((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 9: _t->onPlayingMovie(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
