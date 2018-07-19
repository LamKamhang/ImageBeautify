/*
 * File: art_effect.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 23:08:39 DST 2018
 * -------------------------------------------
 * 艺术特效
 */
#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <cstring>


class ArtEffect
{
    static void _emboss(const cv::Mat &src, cv::Mat &dst);
    static void _sculpture(const cv::Mat &src, cv::Mat &dst);
    static void _dilate(const cv::Mat &src, cv::Mat &dst, int shape = MORPH_RECT, int size = 5);
    static void _erode(const cv::Mat &src, cv::Mat &dst, int shape = MORPH_RECT, int size = 5);
}