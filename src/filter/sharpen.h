#ifndef SHARPEN_H
#define SHARPEN_H
#include <opencv2/opencv.hpp>
using namespace cv;

class sharpen
{
public:
    sharpen();
    Mat sharpenPhoto(Mat p);
};

#endif // SHARPEN_H
