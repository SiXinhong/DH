#ifndef WORKER_H
#define WORKER_H
#include <QThread>
#include "myinterface.h"
#include "dahuainterface.h"
#include "configutil.h"
#include "mainwindow.h"

class Worker:public QThread
{
public:
    Worker();
    void run();
    MainWindow *wm;
    MyInterface *inter;
};

#endif // WORKER_H
