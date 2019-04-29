#ifndef CVUTIL_H
#define CVUTIL_H

#include <QImage>

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class CVUtil
{
public:
    CVUtil();


    static Scalar getRandomColor(int id);
    static cv::Mat QImageToMat(QImage image);
    static QImage MatToQImage(const cv::Mat& mat);
    static void paintScale(Mat image,double startw,double starth, double endw, double endy,int widget);
    static QPixmap cvMatToQPixmap( const cv::Mat &inMat);
};

#endif // CVUTIL_H
