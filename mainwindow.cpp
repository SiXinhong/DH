#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>

#include <QGridLayout>
#include <cv.h>

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "cvutil.h"
#include <QDebug>
#include <QTime>
#include "hkinterface.h"
#include "worker.h"
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QDir>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConfigUtil::readConfigs();

    if(ConfigUtil::isOpenCam == 1){
        inter = new HkInterface();
    }
    else if(ConfigUtil::isOpenCam == 2){
        inter = new DahuaInterface();
    }else{
        QMessageBox::critical(NULL,"error","未指定摄像头", QMessageBox::Close, QMessageBox::Close);
        exit(0);
    }

    inter->setLogin(ConfigUtil::ip, ConfigUtil::user,
                    ConfigUtil::passwd, ConfigUtil::port);
    for(int i=0;!inter->isLogin && i<5;i++){
        inter->login();
    }

    if(!inter->isLogin){
        QMessageBox::critical(NULL,"error","登录失败", QMessageBox::Close, QMessageBox::Close);
        exit(0);
    }

    Worker *worker = new Worker();
    worker->wm = this;
    worker->inter = this->inter;

    worker->start();

    /**
     *菜单栏
     */
    menubar = new QMenuBar(this);
    ToolMenu = new QMenu("工具");
    figure = new QAction("屏幕截图",this);
    figure->setShortcut(Qt::Key_F7);
    ToolMenu->addAction(figure);
    connect(figure,SIGNAL(triggered()),this,SLOT(figureClicked()));
    menubar->addMenu(ToolMenu);


    QWidget* widget = new QWidget(this);
    label = new QLabel(widget);
    gridlayout = new QGridLayout();
    gridlayout->addWidget(label);
    widget->setLayout(gridlayout);
    this->setMenuBar(menubar);
    this->setCentralWidget(widget);
    timer=new QTimer();
    timer->setInterval(40);
    connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));
    timer->start();

    this->setWindowState(Qt::WindowMaximized);
    this->show();
}
void MainWindow::figureClicked(){
    QString timeStr = QDateTime::currentDateTime().toString("/yyyy年MM月dd日hh时mm分ss秒");

    QPixmap pixmap = this->pixmap;

    QString path;
    bool exist = false;
    if(ConfigUtil::screenshotpath.length() > 0){
        QDir *directory = new QDir();
        exist = directory->exists(ConfigUtil::screenshotpath);
        if(!exist){
            exist = directory->mkpath(ConfigUtil::screenshotpath);
        }
        delete directory;
    }

    if(!exist){
        qDebug()<<"设置截图存储路径失败，使用默认路径"<<ConfigUtil::screenshotpath;
        path = QString("./screenshots");
    }else{
        path = ConfigUtil::screenshotpath;
    }
    pixmap.save(path + timeStr + "-无光标.png","PNG");

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

    pixmap.save(path + timeStr + "-有光标.png","PNG");
    QMessageBox::information(this,"屏幕截图","截屏保存成功！",QMessageBox::Ok);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gridlayout;
}

void MainWindow::resizeEvent(QResizeEvent *){

}

void MainWindow::onTimerOut(){
    if(this->pixmap.size().height()<1)
        return;
    QPixmap pixmap = this->pixmap;

    int w = pixmap.width();
    int h = pixmap.height();
    int a = h/2-23;
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
    this->label->setPixmap(pixmap);
    this->label->setScaledContents(true);
}
