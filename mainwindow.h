#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QToolButton>

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
#include "configutil.h"
#include "myinterface.h"
#include <QAction>
#include <QMenuBar>
#include <QMenu>

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setLayout();
    QLabel *label;
    MyInterface *inter;
    QGridLayout *gridlayout;
    QPixmap pixmap;//为什么不直接在worker线程对label.setPixmap,因为画面切换时主线程刷新会使用label里的pixmap，并发设置会导致主线程使用了已销毁的pixmap，这里在主线程通过timer实现
private:
    QTimer *timer;
    Ui::MainWindow *ui;

    QMenuBar* menubar;
    QMenu* ToolMenu;
    QAction* figure;
public:

public slots:
  void resizeEvent(QResizeEvent *);
  void onTimerOut();
  void figureClicked();
};

#endif // MAINWINDOW_H
