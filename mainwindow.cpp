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
#include "worker.h"
#include <QMessageBox>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConfigUtil::readConfigs();

    inter = new DahuaInterface();
    if(ConfigUtil::isOpenCam != 0){
        inter->setLogin(ConfigUtil::ip, ConfigUtil::user,
                        ConfigUtil::passwd, ConfigUtil::port);
        for(int i=0;!inter->isLogin && i<5;i++){
            inter->login();
        }
    }
    if(!inter->isLogin){
        QMessageBox::critical(NULL,"error","登录失败", QMessageBox::Close, QMessageBox::Close);
        return;
    }

    Worker *worker = new Worker();
    worker->wm = this;
    worker->inter = this->inter;

    worker->start();

    QWidget* widget = new QWidget(this);
    label = new QLabel(widget);
    gridlayout = new QGridLayout();
    gridlayout->addWidget(label);
    widget->setLayout(gridlayout);

    this->setCentralWidget(widget);

    timer=new QTimer();
    timer->setInterval(40);
    connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));
    timer->start();

    this->setWindowState(Qt::WindowMaximized);
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gridlayout;
}

void MainWindow::resizeEvent(QResizeEvent *){
}

void MainWindow::onTimerOut(){
    this->label->setPixmap(this->pixmap);
}
