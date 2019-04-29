#include "configutil.h"
#include <QSettings>

ConfigUtil::ConfigUtil()
{

}

int ConfigUtil::isOpenCam;
QString ConfigUtil::ip;
QString ConfigUtil::user;
QString ConfigUtil::passwd;
int ConfigUtil::port;

void ConfigUtil::readConfigs(){
    ConfigUtil::readCamConfigs();
    ConfigUtil::readOtherConfigs();
}

void ConfigUtil::readCamConfigs(){

    QString iniFilePath = "./config/camConfig.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);

    QString switchconfig = settings.value(QString("switch/interface")).toString();
    if(switchconfig == QString("dh")){
        ConfigUtil::isOpenCam = 2;
        ConfigUtil::ip = settings.value(QString("dhconfig/ip")).toString();
        ConfigUtil::user = settings.value(QString("dhconfig/user")).toString();
        ConfigUtil::passwd = settings.value(QString("dhconfig/passwd")).toString();
        ConfigUtil::port = settings.value(QString("dhconfig/port")).toInt();
    }else{
        ConfigUtil::isOpenCam = 0;
    }
}

void ConfigUtil::readOtherConfigs(){

}
