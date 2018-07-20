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
public:
    // 浮雕
    static void _emboss(const cv::Mat &src, cv::Mat &dst);
    // 雕刻
    static void _sculpture(const cv::Mat &src, cv::Mat &dst);
    // 膨胀
    static void _dilate(const cv::Mat &src, cv::Mat &dst);
    // 腐蚀
    static void _erode(const cv::Mat &src, cv::Mat &dst);
    // 磨砂玻璃
    static void _frostGlass(const cv::Mat &src, cv::Mat &dst);
    // 手稿
    static void _sketch(const cv::Mat &src, cv::Mat &dst);
    // 油画
    static void _oilPaint(const cv::Mat &src, cv::Mat &dst);
    // 木刻
    static void _woodCut(const cv::Mat &src, cv::Mat &dst);
    // 反色
    static void _inverted(const cv::Mat &src, cv::Mat &dst);
    // 回忆
    static void _memory(const cv::Mat &src, cv::Mat &dst);
    // 冰冻
    static void _freezing(const cv::Mat &src, cv::Mat &dst);
    // 熔铸
    static void _casting(const cv::Mat &src, cv::Mat &dst);
    // 黑白漫画
    static void _comicStrip(const cv::Mat &src, cv::Mat &dst);
};
