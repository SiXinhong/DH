#ifndef HKINTERFACE_H
#define HKINTERFACE_H

#include <HCNetSDK.h>
#include "myinterface.h"

class HkInterface :  public MyInterface
{
    Q_OBJECT
public:
    HkInterface();
    HkInterface(QString ip,QString userName,QString passwd,int port);
    QPixmap getPixmap();
    bool login();
    LPNET_DVR_JPEGPARA JpegPara;//获取图片时的参数，图片质量
};

#endif // HKINTERFACE_H
