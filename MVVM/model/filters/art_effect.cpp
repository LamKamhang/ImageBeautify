#include "art_effect.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <cstring>

using namespace std;

// 浮雕
void ArtEffect::_emboss(const cv::Mat &src, cv::Mat &dst)
{
    cv::Mat img = src.clone();
	for (int y=1; y<src.rows-1; y++)
	{
        const uchar *p0 = src.ptr<uchar>(y);
        const uchar *p1 = src.ptr<uchar>(y+1);
 
		uchar *img_ptr = img.ptr<uchar>(y);
		for (int x=1; x<src.cols-1; x++)
		{
			for (int i=0; i<3; i++)
			{
				int temp = p1[3*(x+1)+i]-p0[3*(x-1)+i]+128;//浮雕
				if (temp<0)
					img_ptr[3*x+i]=0;
				else if(temp>255)
					img_ptr[3*x+i]=255;
				else
					img_ptr[3*x+i]=temp;
			}
		}
	}
    cv::cvtColor(img, dst, CV_BGR2GRAY);
    cv::normalize(dst, dst, 255, 0, CV_MINMAX);
}

// 雕刻
void ArtEffect::_sculpture(const cv::Mat &src, cv::Mat &dst)
{
    cv::Mat img = src.clone();
	for (int y=1; y<src.rows-1; y++)
	{
        const uchar *p0 = src.ptr<uchar>(y);
        const uchar *p1 = src.ptr<uchar>(y+1);
 
		uchar *img_ptr = img.ptr<uchar>(y);
		for (int x=1; x<src.cols-1; x++)
		{
			for (int i=0; i<3; i++)
			{ 
				int temp = p0[3*(x-1)+i]-p1[3*(x+1)+i]+128;//雕刻
				if (temp<0)
					img_ptr[3*x+i]=0;
				else if(temp>255)
					img_ptr[3*x+i]=255;
				else
					img_ptr[3*x+i]=temp;
			}
		}
	}
    cv::cvtColor(img, dst, CV_BGR2GRAY);
    cv::normalize(dst, dst, 255, 0, CV_MINMAX);
}

// 虚幻
void ArtEffect::_dilate(const cv::Mat &src, cv::Mat &dst)
{
    cv::Mat tmp = src.clone();
    for (int i = 0; i < 2; ++i)
    {
        cv::dilate(tmp, tmp, getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
    }
    tmp.copyTo((dst));
}

// 惊悚
void ArtEffect::_erode(const cv::Mat &src, cv::Mat &dst)
{
    cv::Mat tmp = src.clone();
    for (int i = 0; i < 1; ++i)
    {
        cv::erode(tmp, tmp, getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
    }
    tmp.copyTo(dst);
}

// 磨砂玻璃
void ArtEffect::_frostGlass(const cv::Mat &src, cv::Mat &dst)
{
    cv::RNG rng;
	int randomNum; 
	int Number = 5; 
    cv::Mat tmp = src.clone();
	for (int i = 0; i < src.rows - Number; i++) 
	for (int j = 0; j < src.cols - Number; j++) 
	{ 
		randomNum = rng.uniform(0, Number); 
        tmp.at<cv::Vec3b>(i, j)[0] = src.at<cv::Vec3b>(i + randomNum, j + randomNum)[0];
        tmp.at<cv::Vec3b>(i, j)[1] = src.at<cv::Vec3b>(i + randomNum, j + randomNum)[1];
        tmp.at<cv::Vec3b>(i, j)[2] = src.at<cv::Vec3b>(i + randomNum, j + randomNum)[2];
	}
	tmp.copyTo(dst);
}

// 手稿
void ArtEffect::_sketch(const cv::Mat &src, cv::Mat &dst)
{
	int width=src.cols;
	int heigh=src.rows;
    cv::Mat gray0, gray1;
	//去色
    cv::cvtColor(src,gray0,CV_BGR2GRAY);
	//反色
    cv::addWeighted(gray0,-1,NULL,0,255,gray1);
	//高斯模糊,高斯核的Size与最后的效果有关
    cv::GaussianBlur(gray1,gray1,cv::Size(11,11),0);
 
	//融合：颜色减淡
    cv::Mat img = gray1.clone();
	for (int y=0; y<heigh; y++)
	{
 
		uchar* P0  = gray0.ptr<uchar>(y);
		uchar* P1  = gray1.ptr<uchar>(y);
		uchar* P  = img.ptr<uchar>(y);
		for (int x=0; x<width; x++)
		{
			int tmp0=P0[x];
			int tmp1=P1[x];
			P[x] =(uchar) min((tmp0+(tmp0*tmp1)/(256-tmp1)),255);
		} 
	}
	img.copyTo(dst);
}

// 油画
void ArtEffect::_oilPaint(const cv::Mat &src, cv::Mat &dst)
{
    cv::Mat tmp = src.clone();
	for(int j=0;j<src.rows-2;j++)
	{
		//const uchar*current=src.ptr<const uchar>(j);//当前行
		const uchar*next1=src.ptr<const uchar>(j+1);//后1行
		const uchar*next2=src.ptr<const uchar>(j+2);//后两行
		const uchar*next=next1;
		uchar *output=tmp.ptr<uchar>(j);
		for(int i=0;i<src.cols-2;++i)
		{
			//随机使用相邻点 2.5piexl内
			if(rand()%2)
             next=next2;
			else next=next1;
				int count=3*(i+1);
			if(rand()%2)
				count=3*(i+2);
			else count=3*(i+1);
 
			for (int ch=0;ch<3;++ch)
			{ 
				output[3*i+ch]=next[count+ch];
			}
		}			
	}
	tmp.copyTo(dst);
}

// 木刻
void ArtEffect::_woodCut(const cv::Mat &src, cv::Mat &dst)
{
    cv::Mat tmp = src.clone();
	for(int j=0;j<src.rows;j++)
	{
		const uchar*current=src.ptr<const uchar>(j);//当前行
		uchar *output=tmp.ptr<uchar>(j);
		for(int i=0;i<src.cols;++i)
		{
			if((current[3*i+0]+current[3*i+1]+current[3*i+2])/3>128)
				output[3*i+0]=output[3*i+1]=output[3*i+2]=0;
			else
		      output[3*i+0]=output[3*i+1]=output[3*i+2]=255;
		}
    }
	tmp.copyTo(dst);
}

// 反色
void ArtEffect::_inverted(const cv::Mat &src, cv::Mat &dst)
{
    cv::Mat tmp = src.clone();
    dst = 255 - tmp;
}

// 回忆
void ArtEffect::_memory(const cv::Mat &src, cv::Mat &dst)
{
	int width=src.cols;
	int heigh=src.rows;
    cv::Mat img = src.clone();
	for (int y=0; y<heigh; y++)
	{
        const uchar* P0  = src.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
		for (int x=0; x<width; x++)
		{
			float B=P0[3*x];
			float G=P0[3*x+1];
			float R=P0[3*x+2];
			float newB=0.272*R+0.534*G+0.131*B;
			float newG=0.349*R+0.686*G+0.168*B;
			float newR=0.393*R+0.769*G+0.189*B;
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

// 冰冻
void ArtEffect::_freezing(const cv::Mat &src, cv::Mat &dst)
{
    int width=src.cols;
    int heigh=src.rows;
    cv::Mat tmp = src.clone();
    for (int y=0;y<heigh;y++)
    {
        const uchar* imgP=src.ptr<uchar>(y);
        uchar* dstP=tmp.ptr<uchar>(y);
        for (int x=0;x<width;x++)
        {
            float b0=imgP[3*x];
            float g0=imgP[3*x+1];
            float r0=imgP[3*x+2];

            float b = b0*255/(g0+r0+1);
            float g = g0*255/(b0+r0+1);
            float r = r0*255/(g0+b0+1);

            r = (r>255 ? 255 : (r<0? 0 : r));
            g = (g>255 ? 255 : (g<0? 0 : g));
            b = (b>255 ? 255 : (b<0? 0 : b));

            dstP[3*x] = (uchar)b;
            dstP[3*x+1] = (uchar)g;
            dstP[3*x+2] = (uchar)r;
        }
    }
    tmp.copyTo(dst);
}

// 熔铸
void ArtEffect::_casting(const cv::Mat &src, cv::Mat &dst)
{
    int width=src.cols;
    int heigh=src.rows;
    cv::Mat tmp = src.clone();
    for (int y=0;y<heigh;y++)
    {
        const uchar* imgP=src.ptr<uchar>(y);
        uchar* dstP=tmp.ptr<uchar>(y);
        for (int x=0;x<width;x++)
        {
            float b0=imgP[3*x];
            float g0=imgP[3*x+1];
            float r0=imgP[3*x+2];

            float b = (b0-g0-r0)*3/2;
            float g = (g0-b0-r0)*3/2;
            float r = (r0-g0-b0)*3/2;

            r = (r>255 ? 255 : (r<0? -r : r));
            g = (g>255 ? 255 : (g<0? -g : g));
            b = (b>255 ? 255 : (b<0? -b : b));
            dstP[3*x] = (uchar)b;
            dstP[3*x+1] = (uchar)g;
            dstP[3*x+2] = (uchar)r;
        }
    }
    tmp.copyTo(dst);
}

// 连环画
void ArtEffect::_comicStrip(const cv::Mat &src, cv::Mat &dst)
{
	int width=src.cols;
	int heigh=src.rows;
    cv::Mat img = src.clone();
	for (int y=0; y<heigh; y++)
	{
        const uchar* P0  = src.ptr<uchar>(y);
		uchar* P1  = img.ptr<uchar>(y);
		for (int x=0; x<width; x++)
		{
			float B=P0[3*x];
			float G=P0[3*x+1];
			float R=P0[3*x+2];
			float newB=abs(B-G+B+R)*G/256;
			float newG=abs(B-G+B+R)*R/256;
			float newR=abs(G-B+G+R)*R/256;
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
    cv::cvtColor(img,dst,CV_BGR2GRAY);
    cv::normalize(dst,dst,255,0,CV_MINMAX);
}

