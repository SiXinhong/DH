#ifndef CONFIGUTIL_H
#define CONFIGUTIL_H
#include <QString>


class ConfigUtil
{
public:
    ConfigUtil();
    static int isOpenCam;//是否打开摄像头，0不打开，1打开海康摄像头，2打开大华摄像头
    static QString ip;
    static QString user;
    static QString passwd;
    static int port;
    static void readConfigs();

private:
    static void readCamConfigs();
    static void readOtherConfigs();
};

#endif // CONFIGUTIL_H
