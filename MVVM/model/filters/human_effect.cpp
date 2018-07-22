#include "human_effect.h"

using namespace std;
using namespace cv;


void HumanEffect::_whiteFace(const cv::Mat &src, cv::Mat &dst)
{
    Mat matResult;
    Mat tmp(src);
    int bilateralFilterVal = 25;  // 双边模糊系数
    _aux_func(tmp, 1.1, 80);  // 调整对比度与亮度，参数2为对比度，参数3为亮度
    GaussianBlur(tmp, tmp, Size(3, 3), 0, 0); // 高斯模糊，消除椒盐噪声
    bilateralFilter(tmp, matResult, bilateralFilterVal, // 整体磨皮
        bilateralFilterVal * 3, bilateralFilterVal / 3);

    Mat matFinal;

    // 图像增强，使用非锐化掩蔽（Unsharpening Mask）方案。
    cv::GaussianBlur(matResult, matFinal, cv::Size(0, 0), 9);
    cv::addWeighted(matResult, 1.5, matFinal, -0.5, 0, matFinal);
    matFinal.copyTo(dst);
}

void HumanEffect::_beautifyFace(const Mat &src, Mat &dst)
{
    Mat matResult;
    Mat tmp(src);
    int bilateralFilterVal = 30;  // 双边模糊系数
    _aux_func(tmp, 1.1, 60);  // 调整对比度与亮度，参数2为对比度，参数3为亮度
    GaussianBlur(tmp, tmp, Size(5, 5), 0, 0); // 高斯模糊，消除椒盐噪声
    bilateralFilter(tmp, matResult, bilateralFilterVal, // 整体磨皮
        bilateralFilterVal * 2, bilateralFilterVal / 3);

    Mat matFinal;

    // 图像增强，使用非锐化掩蔽（Unsharpening Mask）方案。
    cv::GaussianBlur(matResult, matFinal, cv::Size(0, 0), 9);
    cv::addWeighted(matResult, 1.5, matFinal, -0.5, 0, matFinal);
    matFinal.copyTo(dst);
}

void HumanEffect::_pinkLady(const cv::Mat &src, cv::Mat &dst)
{
    int width=src.cols;
    int heigh=src.rows;
    Mat img(src.size(),CV_8UC3);
    for (int y=0; y<heigh; y++)
    {
        const uchar* P0  = src.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            // 242 158 194
            float B=P0[3*x];
            float G=P0[3*x+1];
            float R=P0[3*x+2];
            float newB=0.47*R+0.31*G+0.37*B;
            float newG=0.38*R+0.25*G+0.31*B;
            float newR=0.59*R+0.38*G+0.47*B;
            if(newB<0)newB=0;
            if(newB>255)newB=255;
            if(newG<0)newG=0;
            if(newG>255)newG=255;
            if(newR<0)newR=0;
            if(newR>255)newR=255;
            P1[3*x] = (uchar)newB;
            P1[3*x+1] = (uchar)newG;
            P1[3*x+2] = (uchar)newR;
        }
    }
    img.copyTo(dst);
}


void HumanEffect::_aux_func(cv::Mat &src, int alpha, int beta)
{
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				src.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(src.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}
}
