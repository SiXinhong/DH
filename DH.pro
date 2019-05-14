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

INCLUDEPATH += .\hcnet\include
INCLUDEPATH += .\dahua\include
LIBS += -L .\install\x64\mingw\lib\libopencv_*.a\
            .\hcnet\lib\HC*.lib\
            .\hcnet\lib\PlayCtrl.lib\
            .\dahua\lib\dh*.lib\
            .\dahua\lib\dhplay.lib
LIBS += -ldbghelp
SOURCES += main.cpp\
        mainwindow.cpp \
    myinterface.cpp \
    cvutil.cpp \
    dahuainterface.cpp \
    configutil.cpp \
    worker.cpp \
    hkinterface.cpp

HEADERS  += mainwindow.h \
    myinterface.h \
    cvutil.h \
    dahuainterface.h \
    configutil.h \
    worker.h \
    hkinterface.h \
    PlayM4.h

FORMS    += mainwindow.ui
