#ifndef MYINTERFACE_H
#define MYINTERFACE_H
#include <QPixmap>
#include <QVector>
#include <Windows.h>
#include "configutil.h"
#include <QMutex>
#include <QWaitCondition>

class ObjectDetection;
class MyInterface :  public QObject
{
    Q_OBJECT
public:
    MyInterface();
    MyInterface(QString ip,QString userName,QString passwd,int port);
    void setLogin(QString ip,QString userName,QString passwd,int port);
    virtual QPixmap getPixmap();
    virtual bool login() = 0;
    bool isLogin;//是否已经登录
    QString ip;
    QString userName;
    QString passwd;
    int port;
    LONG loginId;//登录后返回的登录标识，后续调用都使用这个
    int currentIndex;
    QVector<QPixmap> cache;
    LONG nPort;//播放库通道号
    QPixmap pixmap;
    QMutex mutex;
    QWaitCondition waitCondition;
    int imageStatus;// -1:初始化，不做任何动作0：无图片文件，1：正在被检测，2：检测成功，已存入this.pixmap，3：已读取过this.pixmap
    static MyInterface *interfaces;
    void setPixMap(QPixmap pixmap);
};

#endif // MYINTERFACE_H
