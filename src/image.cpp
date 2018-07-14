#include "image.hpp"

using namespace cv;
using namespace std;

void Image::_blur(uint w, uint h)
{
    blur(old_img, new_img, Size(w, h));
}

void Image::_emboss()
{
}

void Image::_gray()
{
}