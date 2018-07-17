#include "colortoblack.h"
#include <opencv2/opencv.hpp>
#include "transportmandq.h"
using namespace cv;

QImage ColorToBlack::ColorToBlack(QImage P,int per)
{
    TransportMandQ a;
    Mat img = a.QimagetoMat(P);
    Mat temp_1,temp_2;
    Mat img_gray;

    cvtColor(img,temp_1,CV_BGR2GRAY);
    cvtColor(temp_1,img_gray,COLOR_GRAY2BGR);
    addWeighted(img,1-per,img_gray,per,0.0,temp_2);
    QImage result;
    result = a.MattoQimage(temp_2);
    return result;

}
