#include "image.hpp"

using namespace cv;
using namespace std;

void Image::_blur(uint w, uint h)
{
    blur(old_img, new_img, Size(w, h));
}

void Image::_gaussianBlur(uint w, uint h)
{
    GaussianBlur(old_img, new_img, Size(w, h), 0);
}

void Image::_medianBlur(uint ksize)
{
    medianBlur(old_img, new_img, ksize);
}

void Image::_bilateralFilter(double sigmaColor, double sigmaSpace)
{
    bilateralFilter(old_img, new_img, 25, sigmaColor, sigmaSpace);
}

void Image::_emboss()
{
}

void Image::_gray()
{
}