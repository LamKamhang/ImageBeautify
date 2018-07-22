#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <cstring>
#include <math.h>
#include <iostream>

class ClassicEffect
{
public:
	//锐化
	static void _sharpen(const cv::Mat &scr, cv::Mat &dst);
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
	// 美白
	static void _whiteFace(const cv::Mat &src, cv::Mat &dst);
	// 美颜
	static void _beautifyFace(const cv::Mat &src, cv::Mat &dst);
	// 粉红佳人
	static void _pinkLady(const cv::Mat &src, cv::Mat &dst);

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
