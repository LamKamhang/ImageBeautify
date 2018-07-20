#ifndef DEFOG_H
#define DEFOG_H

#include <QObject>
#include <opencv2/opencv.hpp>
using namespace cv;

class defog//这个函数需要存储一些过程图片，所以生成之后务必释放
{
public:
    Mat DeFog( Mat scr );//用这个函数就可以返回需要的图片
    ~defog();

    cv::Mat darkChannelDefog(cv::Mat);//暗原色先验去雾
    Mat guidedDefog(cv::Mat);//导向滤波去雾
    cv::Mat enhanceImage(cv::Mat);//增强
    cv::Mat getTImage();
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

#endif // DEFOG_H
