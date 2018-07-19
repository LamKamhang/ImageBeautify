#include "art_effect.h"

using namespace std;
using namespace cv;

void ArtEffect::_emboss(const cv::Mat &src, cv::Mat &dst)
{
	Mat img(src.size(),CV_8UC3);
	for (int y=1; y<src.rows-1; y++)
	{
		uchar *p0 = src.ptr<uchar>(y);
		uchar *p1 = src.ptr<uchar>(y+1);
 
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
	cvtColor(img, dst, CV_BGR2GRAY);
	normalize(dst, dst, 255, 0, CV_MINMAX);
}

void ArtEffect::_sculpture(const cv::Mat &src, cv::Mat &dst)
{
	Mat img(src.size(),CV_8UC3);
	for (int y=1; y<src.rows-1; y++)
	{
		uchar *p0 = src.ptr<uchar>(y);
		uchar *p1 = src.ptr<uchar>(y+1);
 
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
	cvtColor(img, dst, CV_BGR2GRAY);
	normalize(dst, dst, 255, 0, CV_MINMAX);
}

void ArtEffect::_dilate(const cv::Mat &src, cv::Mat &dst, int shape = MORPH_RECT, int size = 5)
{
	dilate(src, dst, getStructuringElement(shape, Size(size, size)));
}

void ArtEffect::_erode(const cv::Mat &src, cv::Mat &dst, int shape = MORPH_RECT, int size = 5)
{
	erode(src, dst, getStructuringElement(shape, Size(size, size)));
}
