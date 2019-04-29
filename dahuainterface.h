#ifndef DAHUAINTERFACE_H
#define DAHUAINTERFACE_H
#include "dhnetsdk.h"
#include "myinterface.h"

class DahuaInterface : public MyInterface
{
    Q_OBJECT
public:
    DahuaInterface();
    DahuaInterface(QString ip,QString userName,QString passwd,int port);
    QPixmap getPixmap();
    bool login();
};

#endif // DAHUAINTERFACE_H
