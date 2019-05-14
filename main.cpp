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

static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    //And output crash information
    EXCEPTION_RECORD *record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode, 16));
    QString errAddr(QString::number((qulonglong)record->ExceptionAddress, 16));
    QString errFlag(QString::number(record->ExceptionFlags, 16));
    QString errPara(QString::number(record->NumberParameters, 16));
    qDebug()<<"errCode: "<<errCode;
    qDebug()<<"errAddr: "<<errAddr;
    qDebug()<<"errFlag: "<<errFlag;
    qDebug()<<"errPara: "<<errPara;
    //Create the dump file
    HANDLE hDumpFile = CreateFile((LPCWSTR)QString("./crash.dmp").utf16(),
             GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hDumpFile != INVALID_HANDLE_VALUE) {
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
        CloseHandle(hDumpFile);
    }
    return EXCEPTION_EXECUTE_HANDLER;
}

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

//static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
//{
//    return EXCEPTION_EXECUTE_HANDLER;
//}
int main(int argc, char *argv[])
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    //SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    //file.open(QIODevice::ReadWrite | QIODevice::Append);
    //qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("光学瞄准系统");
    w.show();

    return a.exec();
}
