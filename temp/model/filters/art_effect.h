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
        old_img = cv::imread(name);
		new_img = cv::imread(name);
    }

    ~Image() = default;

    // change to another image
    void AttachTo(const std::string &name)
    {
        old_img = cv::imread(name);
		new_img = cv::imread(name);
    }

    void ImgShow(const std::string &windowName) throw(ErrorMsg)
    {
        if (new_img.data == NULL)
            throw ErrorMsg("NULL Image!");
        imshow(windowName, new_img);
    }

    // some process method
    void _blur(uint w = 7, uint h = 7);
    void _gaussianBlur(uint w = 3, uint h = 3);
    void _medianBlur(uint ksize = 5);
    void _bilateralFilter(double sigmaColor = 50, double sigmaSpace = 3);
    void _emboss();
    void _sculpture();
    void _frostGlass();
    void _sketch();
    void _oilPaint();
    void _woodCut();
    void _onTrackbar();
    void _gray(int mode = CV_BGR2GRAY);
	void _inverted();
    void _dilate(int shape = MORPH_RECT, int size = 5);
    void _erode(int shape = MORPH_RECT, int size = 5);
    void _memory();
    void _draw();
    void _freezing();
    void _casting();

private:
    std::string image_name;
    cv::Mat old_img;
    cv::Mat new_img;
};

/*
 * File: art_effect.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 23:08:39 DST 2018
 * -------------------------------------------
 * 艺术特效
 */

class ArtEffect
{
    static void _emboss(const cv::Mat &src, cv::Mat &dst);
    static void _sculpture(const cv::Mat &src, cv::Mat &dst);
    static void _dilate(const cv::Mat &src, cv::Mat &dst, int shape = MORPH_RECT, int size = 5);
    static void _erode(const cv::Mat &src, cv::Mat &dst, int shape = MORPH_RECT, int size = 5);
}