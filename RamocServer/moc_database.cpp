/****************************************************************************
** Meta object code from reading C++ file 'database.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "database.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataBase_t {
    QByteArrayData data[8];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataBase_t qt_meta_stringdata_DataBase = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DataBase"
QT_MOC_LITERAL(1, 9, 11), // "sig_NewInfo"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "sig_PlayedSet"
QT_MOC_LITERAL(4, 36, 21), // "sig_SendUnsortedFiles"
QT_MOC_LITERAL(5, 58, 11), // "onSetPlayed"
QT_MOC_LITERAL(6, 70, 11), // "string_File"
QT_MOC_LITERAL(7, 82, 18) // "onGetUnsortedFiles"

    },
    "DataBase\0sig_NewInfo\0\0sig_PlayedSet\0"
    "sig_SendUnsortedFiles\0onSetPlayed\0"
    "string_File\0onGetUnsortedFiles"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    0,   42,    2, 0x06 /* Public */,
       4,    1,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   46,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

       0        // eod
};

void DataBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataBase *_t = static_cast<DataBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_NewInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sig_PlayedSet(); break;
        case 2: _t->sig_SendUnsortedFiles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->onSetPlayed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->onGetUnsortedFiles(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataBase::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_NewInfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_PlayedSet)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_SendUnsortedFiles)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject DataBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataBase.data,
      qt_meta_data_DataBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DataBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DataBase.stringdata0))
        return static_cast<void*>(const_cast< DataBase*>(this));
    return QObject::qt_metacast(_clname);
}

int DataBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DataBase::sig_NewInfo(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataBase::sig_PlayedSet()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DataBase::sig_SendUnsortedFiles(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
