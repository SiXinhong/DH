#include "myinterface.h"
#include <QTime>
#include <QDebug>
#include <QDir>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "cvutil.h"
#include <QPainter>
#include <QPen>

MyInterface* MyInterface::interfaces;

MyInterface::MyInterface()
{
    currentIndex = 0;
    for(int i=0;i<50;i++){
        cache.append(QPixmap(QString("./image/%1.jpg").arg(i)));
    }

    this->isLogin = false;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+currentIndex);

    this->imageStatus = -1;
}

MyInterface::MyInterface(QString ip,QString userName,QString passwd,int port){
    this->ip = ip;
    this->userName = userName;
    this->passwd = passwd;
    this->port = port;
    currentIndex = 0;
    for(int i=0;i<50;i++){
        cache.append(QPixmap(QString("./image/%1.jpg").arg(i)));
    }

    this->isLogin = false;
}

void MyInterface::setLogin(QString ip,QString userName,QString passwd,int port){
    this->ip = ip;
    this->userName = userName;
    this->passwd = passwd;
    this->port = port;
}
void MyInterface::setPixMap(QPixmap pixmap){
    int w = pixmap.width();
    int h = pixmap.height();
    int a = h/2;
    QPainter painter(&pixmap);
    QPen pen;
    pen.setBrush(Qt::black);
    painter.setPen(pen);

    // 正方形
    painter.drawRect(w/2 - a/2, h/2 - a/2, a, a);
    painter.drawLine(w/2 - a/2, h/2 - a/2, w/2 + a/2, h/2 + a/2);
    painter.drawLine(w/2 - a/2, h/2 + a/2, w/2 + a/2, h/2 - a/2);

    pen.setBrush(Qt::blue);
    painter.setPen(pen);
    int dist = w/30;
    painter.drawLine(2*dist, h/2, w-2*dist, h/2);
    painter.drawLine(w/2, 2*dist, w/2, h-2*dist);

    int wCount = (w/2-3*dist)/dist;
    int wStart = w/2 - wCount*dist;
    int y1 = h/2 - dist;
    int y2 = h/2 + dist;
    int cnt = 0;
    for(int x = wStart; cnt<2*wCount;cnt++,x+=dist){
        painter.drawLine(x, y1, x, y2);
    }
    int hCount = (h/2-3*dist)/dist;
    int hStart = h/2 - hCount*dist;
    int x1 = w/2 - dist;
    int x2 = w/2 + dist;
    cnt = 0;
    for(int y = hStart; cnt<2*hCount; cnt++,y+=dist){
        painter.drawLine(x1, y, x2, y);
    }
    this->pixmap = pixmap;
}

QPixmap MyInterface::getPixmap(){
    currentIndex = (currentIndex+qrand()%10)%50;
    return cache.at(currentIndex);
}
