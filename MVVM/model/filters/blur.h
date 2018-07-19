/*
 * File: blur.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 23:08:39 DST 2018
 * -------------------------------------------
 * 滤波
 */

#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Blur
{
    static void _blur(const cv::Mat &src, cv::Mat &dst, uint w = 7, uint h = 7);
    static void _gaussianBlur(const cv::Mat &src, cv::Mat &dst, uint w = 3, uint h = 3);
    static void _medianBlur(const cv::Mat &src, cv::Mat &dst, uint ksize = 5);
    static void _bilateralFilter(const cv::Mat &src, cv::Mat &dst, double sigmaColor = 50, double sigmaSpace = 3);
}