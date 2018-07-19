#ifndef COLORTOBLACK_H
#define COLORTOBLACK_H
#include <opencv2/opencv.hpp>
using namespace cv;

class ColorToBlack
{
public:
    Mat ColorToBlack(Mat P,int per);
    Mat img;
};

#endif // COLORTOBLACK_H
