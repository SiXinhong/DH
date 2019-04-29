#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>
#include "DbgHelp.h"
#include <QDebug>
#include <QTextCodec>
#include <QMutex>
#include <QDateTime>
#include <QFile>

QFile file("log.txt");

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QByteArray localMsg = msg.toLocal8Bit();
//    if(type == QtDebugMsg){
//        std::cerr<<localMsg.constData()<<std::endl;
//        return;
//    }else if(type == QtWarningMsg){
//        return;
//    }
    // 加锁
    static QMutex mutex;
    mutex.lock();


    // 设置输出信息格式
//    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss-zzz");
//    QString strMessage = QString("%1 %2 File:%3  Line:%4  Function:%5")
//            .arg(strDateTime).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
    QString strMessage = QString("%1").arg(localMsg.constData());

    // 输出信息至文件中（读写、追加形式）
//    QFile file("log.txt");
//    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
//    file.close();

    // 解锁
    mutex.unlock();
}

static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    return EXCEPTION_EXECUTE_HANDLER;
}
int main(int argc, char *argv[])
{
    //SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    //file.open(QIODevice::ReadWrite | QIODevice::Append);
    //qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("XX机场鸟情智能视频监控报警系统");
    w.show();

    return a.exec();
}
