/*
 * File: util.h
 * Version: 1.0
 * Author: kk
 * Created Date: Tue Jul 17 20:24:24 DST 2018
 * -------------------------------------------
 * 提供一下工具函数，方便viewModel层进行转换
 *  - Mat2QImage函数实现将opencv的Mat转换为Qt的QImage
 *  - QImage2Mat函数实现将Qt的QImage转换为opencv的Mat
 */

#pragma once
#include <opencv2/opencv.hpp>
#include <QImage>

class Tools
{
public:

    static cv::Mat QImage2Mat(const QImage &rhs);

    static QImage Mat2QImage(const cv::Mat& rhs);
}
