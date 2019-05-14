#include "configutil.h"
#include <QSettings>
#include <QDebug>

ConfigUtil::ConfigUtil()
{

}

int ConfigUtil::isOpenCam;
QString ConfigUtil::ip;
QString ConfigUtil::user;
QString ConfigUtil::passwd;
int ConfigUtil::port;
QString ConfigUtil::screenshotpath;

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
    }else if(switchconfig == QString("hk")){
        ConfigUtil::isOpenCam = 1;
        ConfigUtil::ip = settings.value(QString("hkconfig/ip")).toString();
        ConfigUtil::user = settings.value(QString("hkconfig/user")).toString();
        ConfigUtil::passwd = settings.value(QString("hkconfig/passwd")).toString();
        ConfigUtil::port = settings.value(QString("hkconfig/port")).toInt();
    }else{
        ConfigUtil::isOpenCam = 0;
    }
}

void ConfigUtil::readOtherConfigs(){
    QString iniFilePath = "./config/commonConfig.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    ConfigUtil::screenshotpath = settings.value(QString("common/screenshotpath")).toString();
    if(ConfigUtil::screenshotpath.length() > 0 &&
            ConfigUtil::screenshotpath.endsWith("/")){
        ConfigUtil::screenshotpath = ConfigUtil::screenshotpath.left(ConfigUtil::screenshotpath.length()-1);
    }
    qDebug()<<"ConfigUtil::screenshotpath"<<ConfigUtil::screenshotpath;
}
