#-------------------------------------------------
#
# Project created by QtCreator 2018-07-14T15:30:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DH
TEMPLATE = app

INCLUDEPATH += .\install\include
INCLUDEPATH += .\install\include\opencv

INCLUDEPATH += .\dahua\include
LIBS += -L .\install\x64\mingw\lib\libopencv_*.a\
            .\dahua\lib\dh*.lib\
            .\dahua\lib\dhplay.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    myinterface.cpp \
    cvutil.cpp \
    dahuainterface.cpp \
    configutil.cpp \
    worker.cpp

HEADERS  += mainwindow.h \
    myinterface.h \
    cvutil.h \
    dahuainterface.h \
    configutil.h \
    worker.h

FORMS    += mainwindow.ui
