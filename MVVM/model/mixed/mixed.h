#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class Mixed
{
public:
    //混合
    static cv::Mat _Hybrid(const cv::Mat &scr,const cv::Mat &dst,double pro);
};

