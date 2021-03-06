#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T20:08:39
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RamocServer
target.path = /usr/bin/
INSTALLS += target

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Wno-reorder

SOURCES += database.cpp\
        insertMovies.cpp\
        main.cpp\
        mainwindow.cpp\
        omxplayer.cpp\
        server.cpp\
        socket.cpp\
        log.cpp\
        m_lastfm.cpp

HEADERS  += constants.h\
            database.h\
            imoviemplayer.h\
            insertMovies.h\
            log.h\
            mainwindow.h\
            omxplayer.h\
            server.h\
            socket.h\
            m_lastfm.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc 
LIBS += -L/usr/lib \
    -ltag
LIBS += -L/usr/lib \
    -lqjson

INCLUDEPATH += /usr/include/taglib
