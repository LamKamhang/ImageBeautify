/*
 * File: human_effect.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 23:08:39 DST 2018
 * -------------------------------------------
 * 人像特效
 */
#pragma once

#include <opencv2/opencv.hpp>
#include <string>


class HumanEffect
{
public:
    static void _whiteFace(const cv::Mat &src, cv::Mat &dst);
    static void _beautifyFace(const cv::Mat &src, cv::Mat &dst);
    static void _pinkLady(const cv::Mat &src, cv::Mat &dst);
private:
    static void _aux_func(cv::Mat &src, int alpha, int beta);
};
