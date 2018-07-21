#include "basic_effect.h"


using namespace std;

void BasicEffect::_sharpen(const cv::Mat &scr, cv::Mat &dst)
{
    cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
    kernel.at<float>(1,1) = 5;
    kernel.at<float>(0,1) = -1;
    kernel.at<float>(2,1) = -1;
    kernel.at<float>(1,0) = -1;
    kernel.at<float>(1,2) = -1;
    cv::filter2D(scr,dst,scr.depth(),kernel);
    dst.row(0).setTo(cv::Scalar(0,0,0));
    dst.row(dst.rows-1).setTo(cv::Scalar(0,0,0));
    dst.col(0).setTo(cv::Scalar(0,0,0));
    dst.col(dst.cols-1).setTo(cv::Scalar(0,0,0));
}

void BasicEffect::_inversecolor(const cv::Mat &scr, cv::Mat &dst)
{
    cv::Mat temp;
    temp = 255 -scr;
    dst = temp.clone();
}

void BasicEffect::_colortoblack(const cv::Mat &scr, cv::Mat &dst)
{
    cv::Mat temp_1;

    cv::cvtColor(scr,temp_1,CV_BGR2GRAY);
    cv::cvtColor(temp_1,dst,cv::COLOR_GRAY2BGR);
}

void BasicEffect::_defog(const cv:: Mat &scr,cv::Mat &dst)
{
    cv::Mat c;
    cv::Mat b = scr.clone();
    defog a;
    c = a.DeFog(b);
    dst = c.clone();
    a.~defog();
}

cv::Mat defog::DeFog(cv::Mat scr)
{
    cv::Mat a = darkChannelDefog(scr);
    cv::Mat b = getTImage();
    cv::Mat c = enhanceImage(a);
    return a;
}

defog::~defog()
{

}

cv::Mat defog::minRGB(cv::Mat src)
{
    cv::Mat minRgb;
    if(src.empty())
        return minRgb;

    minRgb= cv::Mat::zeros(src.rows,src.cols,CV_8UC1);
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            uchar g_minvalue =255;
            for(int c=0;c<3;c++)
            {
                if(g_minvalue>src.at<cv::Vec3b>(i,j)[c])
                    g_minvalue=src.at<cv::Vec3b>(i,j)[c];
            }
            minRgb.at<uchar>(i,j)=g_minvalue;
        }
    return minRgb;
}

cv::Mat defog::minFilter(cv::Mat src, int ksize)
{
    cv::Mat dst;
    if(src.channels()!=1)
        return dst  ;
    if(src.depth()>8)
        return dst;

    int r=(ksize-1)/2;

    dst=cv::Mat::zeros(src.rows,src.cols,CV_8UC1);


    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            int top=i-r;
            int bottom=i+r;
            int left=j-r;
            int right=j+r;
            if(i-r<0)
                top=0;
            if(i+r>src.rows)
                bottom=src.rows;
            if(j-r<0)
                left=0;
            if(j+r>src.cols)
                right=src.cols;
            cv::Mat ImROI=src(cv::Range(top,bottom),cv::Range(left,right));
            double min,max;
            cv::minMaxLoc(ImROI,&min,&max,0,0);
            dst.at<uchar>(i,j)=min;
        }
    return dst;
}

cv::Mat defog::grayStretch(const cv::Mat src, double lowcut, double highcut)
{
    const int bins = 256;
    int hist_size=bins;
    float range[]={0,255};
    const float* ranges[]={range};
    cv::MatND desHist;
    int channels=0;
    cv::calcHist(&src,1,&channels,cv::Mat(),desHist,1,&hist_size,ranges,true,false);
    int pixelAmount=src.rows*src.cols;
    float Sum=0;
    int minValue,maxValue;
    for(int i=0;i<bins;i++)
    {
        Sum=Sum+desHist.at<float>(i);
        if(Sum>=pixelAmount*lowcut*0.01)
        {
            minValue=i;
            break;
        }
    }

    Sum=0;
    for(int i=bins-1;i>=0;i--)
    {
        Sum=Sum+desHist.at<float>(i);
        if(Sum>=pixelAmount*highcut*0.01)
        {
            maxValue=i;
            break;
        }
    }

    cv::Mat dst=src;
    if(minValue>maxValue)
        return src;

    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            if(src.at<uchar>(i,j)<minValue)
                dst.at<uchar>(i,j)=0;
            if(src.at<uchar>(i,j)>maxValue)
                dst.at<uchar>(i,j)=255;
            else
            {
                double pixelValue=((src.at<uchar>(i,j)-minValue)/
                                   (double)(maxValue-minValue))*255;
                dst.at<uchar>(i,j)=(int)pixelValue;
            }
        }


    return dst;
}

cv::Mat defog::darkChannelDefog(cv::Mat src)
{
    cv::Mat tempImage=minRGB(src);

    int ksize=std::max(3,std::max((int)(src.cols*kernRatio),
                                  (int)(src.rows*kernRatio)));
    tempImage=minFilter(tempImage,ksize);

    m_tImage=cv::Mat::zeros(src.rows,src.cols,CV_64FC1);
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
            m_tImage.at<double>(i,j)=((255.0-
                                       (double)tempImage.at<uchar>(i,j)*wFactor)/255)-0.005;

    double A[3];cv::Point maxLoc;
    cv::minMaxLoc(tempImage,0,0,0,&maxLoc);
    for(int c=0;c<src.channels();c++)
        A[c]=src.at<cv::Vec3b>(maxLoc.y,maxLoc.x)[c];
    m_dstImage=cv::Mat::zeros(src.rows,src.cols,CV_64FC3);
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
            for(int c=0;c<src.channels();c++)
                m_dstImage.at<cv::Vec3d>(i,j)[c]=(src.at<cv::Vec3b>(i,j)[c]-
                                              (1-m_tImage.at<double>(i,j))*A[c])/
                        std::max(m_tImage.at<double>(i,j),min_t);
    m_dstImage.convertTo(m_dstImage,CV_8UC3);


    return m_dstImage;

}

cv::Mat defog::enhanceImage(cv::Mat src)
{
    cv::Mat dst;
    cv::Mat channels[3];
    cv::split(src,channels);
    for(int c=0;c<3;c++)
        channels[c]= grayStretch(channels[c],0.001,1);
    cv::merge(channels,3,dst);

    return dst;
}

cv::Mat defog::getTImage()
{
    cv::Mat temp = cv::Mat::zeros(m_tImage.rows,m_tImage.cols,CV_8UC1);
    for(int i=0;i<m_tImage.rows;i++)
        for( int j=0;j<m_tImage.cols;j++)
        {
            temp.at<uchar>(i,j) = (int)(m_tImage.at<double>(i,j)*255);
        }
    m_tImage.convertTo(m_tImage,CV_8UC1);
    m_tImage = temp;
    return m_tImage;
}

void BasicEffect::_balance(const cv::Mat &scr,cv::Mat &dst)
{
    cv::Mat image = dst.clone();
    cv::Mat mergeImg;


    vector<cv::Mat> splitBGR(image.channels());

    cv::split(image,splitBGR);


    for(int i=0; i<image.channels(); i++)

        cv::equalizeHist(splitBGR[i],splitBGR[i]);


    cv::merge(splitBGR,mergeImg);
    dst = mergeImg.clone();
}

void BasicEffect::_soft(const cv::Mat &scr,cv::Mat &dst)
{
    cv::Mat temp = scr.clone();
    cv::GaussianBlur(temp,dst,cv::Size(1,1),0);
}
