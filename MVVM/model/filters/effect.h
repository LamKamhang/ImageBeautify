#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <cstring>
#include <math.h>
#include <iostream>

class effect
{
public:
    // 浮雕
    static void _emboss(const cv::Mat &src, cv::Mat &dst);
    // 雕刻
    static void _sculpture(const cv::Mat &src, cv::Mat &dst);
    // 虚幻
    static void _dilate(const cv::Mat &src, cv::Mat &dst);
    // 惊悚
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
   //怀旧
  static void _nostalgia(const cv::Mat &scr,cv::Mat &dst);
  //连环画
  static void _BlackComic(const cv::Mat &scr,cv::Mat &dst);
  //时光隧道
  static void _timetuunel(const cv::Mat &scr,cv::Mat &dst);
  //经典lomo
  static void _classiclomo(const cv::Mat &scr,cv::Mat &dst);
    static void _whiteFace(const cv::Mat &src, cv::Mat &dst);
    static void _beautifyFace(const cv::Mat &src, cv::Mat &dst);
    static void _pinkLady(const cv::Mat &src, cv::Mat &dst);

    static void _blur(const cv::Mat &src, cv::Mat &dst, uint w = 7, uint h = 7);
    static void _gaussianBlur(const cv::Mat &src, cv::Mat &dst, uint w = 3, uint h = 3);
    static void _medianBlur(const cv::Mat &src, cv::Mat &dst, uint ksize = 5);
    static void _bilateralFilter(const cv::Mat &src, cv::Mat &dst, double sigmaColor = 50, double sigmaSpace = 3);
private:
    static void _aux_func(cv::Mat &src, int alpha, int beta);
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
