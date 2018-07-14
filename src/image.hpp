#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <cstring>
#include "exception.h"

class Image
{
public:
    
    // constructor and destructor
    Image():
        image_name(""), old_img(), new_img()
    {
    }

    Image(const std::string &name):
        image_name(name)
    {
        new_img = old_img = cv::imread(name);
    }

    ~Image() = default;

    // change to another image
    void AttachTo(const std::string &name)
    {
        new_img = old_img = cv::imread(name);
    }

    void ImgShow(const std::string &windowName) throw(ErrorMsg)
    {
        if (new_img.data == NULL)
            throw ErrorMsg("NULL Image!");
        imshow(windowName, new_img);
    }

    // some process method
    void _blur(uint w = 7, uint h = 7);
    void _emboss();
    void _gray();

private:
    std::string image_name;
    cv::Mat old_img;
    cv::Mat new_img;
};