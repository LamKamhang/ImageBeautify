/*
 * File: basic_effect.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 23:08:39 DST 2018
 * -------------------------------------------
 * 基础特效
 */

#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <math.h>

class BasicEffect
{
public:
    //锐化
   static void _sharpen(const cv::Mat &scr, cv::Mat &dst);
   //反色
   static void _inversecolor(const cv::Mat &scr, cv::Mat &dst);
   //黑白
   static void _colortoblack(const cv::Mat &scr, cv::Mat &dst);
   //去雾气
   static void _defog(const cv:: Mat &scr,cv::Mat &dst);
   //柔和
   static void _soft(const cv::Mat &scr,cv::Mat &dst);
   //均衡图
   static void _balance(const cv::Mat &scr,cv::Mat &dst);
   //
};

class defog
{
public:
    Mat DeFog( Mat scr );
    ~defog();

    cv::Mat darkChannelDefog(cv::Mat);
    cv::Mat enhanceImage(cv::Mat);
    cv::Mat getTImage();
public:
    const double kernRatio=0.01;
    const double minAtomLigth=220;
    const double wFactor=0.95;
    const double min_t =0.1;
private:
    cv::Mat minRGB(cv::Mat);
    cv::Mat minFilter(cv::Mat src,int ksize=3);
    cv::Mat guildFilter(cv::Mat g,cv::Mat p,int ksize);
    cv::Mat grayStretch(const cv::Mat src,double lowcut,double highcut);
private:
    cv::Mat m_srcImage;
    cv::Mat m_tImage;
    cv::Mat m_dstImage;
};
