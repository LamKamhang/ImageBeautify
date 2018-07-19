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

class BasicEffect
{
   static void _sharpen(const cv::Mat &scr, cv::Mat &dst);
   static void _inversecolor(const cv::Mat &scr, cv::Mat &dst);
   static void _colortoblack(const cv::Mat &scr, cv::Mat &dst);
   static void _defog(const cv:: Mat &scr,cv::Mat &dst);
};

class defog
{
public:
    Mat DeFog( Mat scr );//用这个函数就可以返回需要的图片
    ~defog();

    cv::Mat darkChannelDefog(cv::Mat);//暗原色先验去雾
    Mat guidedDefog(cv::Mat);//导向滤波去雾
    cv::Mat enhanceImage(cv::Mat);//增强
    cv::Mat getTImage();
public:
    const double kernRatio=0.01; //自适应核比例
    const double minAtomLigth=220; //最小大气光强
    const double wFactor=0.95; //w系数 用来调节
    const double min_t =0.1; //最小透射率
private:
    cv::Mat minRGB(cv::Mat);
    cv::Mat minFilter(cv::Mat src,int ksize=3);
    cv::Mat guildFilter(cv::Mat g,cv::Mat p,int ksize);
    cv::Mat grayStretch(const cv::Mat src,double lowcut,double highcut);
private:
    cv::Mat m_srcImage; //原始图像
    cv::Mat m_tImage;  //透射率
    cv::Mat m_dstImage; //结果图像
};
