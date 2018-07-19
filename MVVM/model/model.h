/*
 * File: model.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 19:19:59 DST 2018
 * -------------------------------------------
 * 构建Model类
 */
#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include "../common/etlbase.h"


class Model
    : public Proxy_PropertyNotification<Model>
{
public:
    Model(){}
    const cv::Mat& getShow();
    const cv::Mat& getOrigin();

    // basic methods.
    void open_file(const std::string &path) throw(errorType);
    void save_file(const std::string &path);
    void reset() throw(errorType);
    
    // image operation.

private:
    cv::Mat originImg;
    cv::Mat showImg;
    cv::Mat tmpImg;
};
