#ifndef TRANSPORTMANDQ_H
#define TRANSPORTMANDQ_H

#include <opencv2/opencv.hpp>
#include <QImage>
using namespace cv;

class TransportMandQ
{
public:
    Mat QimagetoMat(QImage P);
    QImage MattoQimage(Mat P);
};

#endif // TRANSPORTMANDQ_H
