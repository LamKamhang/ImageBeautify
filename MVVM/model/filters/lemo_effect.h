/*
 * File: lemo_effect.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 23:08:39 DST 2018
 * -------------------------------------------
 * LEMO特效
 */
#pragma once

#include <opencv2/opencv.hpp>
#include <string>


class LemoEffect
{
   static void _nostalgia(const cv::Mat &scr,cv::Mat &dst);//怀旧
   static void _BlackComic(const cv::Mat &scr,cv::Mat &dst);//连环画
   static void _timetuunel(const cv::Mat &scr,cv::Mat &dst);//时光隧道
}
