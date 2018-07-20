#include "blur.h"

using namespace std;
using namespace cv;

void Blur::_blur(const Mat &src, Mat &dst, uint w, uint h)
{
    blur(src, dst, Size(w, h));
}

void Blur::_gaussianBlur(const Mat &src, Mat &dst, uint w, uint h)
{
    GaussianBlur(src, dst, Size(w, h), 0);
}

void Blur::_medianBlur(const Mat &src, Mat &dst, uint ksize)
{
    medianBlur(src, dst, ksize);
}

void Blur::_bilateralFilter(const Mat &src, Mat &dst, double sigmaColor, double sigmaSpace)
{
	bilateralFilter(src, dst, 0, sigmaColor, sigmaSpace);
}