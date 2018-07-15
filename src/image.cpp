#include "image.hpp"

using namespace cv;
using namespace std;

void Image::_blur(uint w, uint h)
{
    blur(old_img, new_img, Size(w, h));
}

void Image::_gaussianBlur(uint w, uint h)
{
    GaussianBlur(old_img, new_img, Size(w, h), 0);
}

void Image::_medianBlur(uint ksize)
{
    medianBlur(old_img, new_img, ksize);
}

void Image::_bilateralFilter(double sigmaColor, double sigmaSpace)
{
	bilateralFilter(old_img, new_img, 0, sigmaColor, sigmaSpace);
}

void Image::_emboss()
{
	Mat img(old_img.size(),CV_8UC3);
	for (int y=1; y<old_img.rows-1; y++)
	{
		uchar *p0 = old_img.ptr<uchar>(y);
		uchar *p1 = old_img.ptr<uchar>(y+1);
 
		uchar *img_ptr = img.ptr<uchar>(y);
		for (int x=1; x<old_img.cols-1; x++)
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
	cvtColor(img, new_img, CV_BGR2GRAY);
	normalize(new_img,new_img,255,0,CV_MINMAX);
}

void Image::_sculpture()
{
	Mat img(new_img.size(),CV_8UC3);
	for (int y=1; y<old_img.rows-1; y++)
	{
		uchar *p0 = old_img.ptr<uchar>(y);
		uchar *p1 = old_img.ptr<uchar>(y+1);
 
		uchar *img_ptr = img.ptr<uchar>(y);
		for (int x=1; x<old_img.cols-1; x++)
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
	cvtColor(img, new_img, CV_BGR2GRAY);
	normalize(new_img,new_img,255,0,CV_MINMAX);
}

void Image::_gray(int mode)
{
	cvtColor(old_img, new_img, mode);
	normalize(new_img,new_img,255,0,CV_MINMAX);
}

void Image::_inverted()
{
	new_img = 255 - old_img;
}

void Image::_dilate(int shape, int size)
{
    dilate(old_img, new_img, getStructuringElement(shape, Size(size, size)));    
}

void Image::_erode(int shape, int size)
{
    erode(old_img, new_img, getStructuringElement(shape, Size(size, size)));
}

void Image::_memory()
{
    int width=old_img.cols;
	int heigh=old_img.rows;
	Mat img(old_img.size(),CV_8UC3);
	for (int y=0; y<heigh; y++)
	{
		uchar* P0  = old_img.ptr<uchar>(y);
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
    img.copyTo(new_img);
}

void Image::_frostGlass()
{
	RNG rng; 
	int randomNum; 
	int Number = 5; 

	for (int i = 0; i < old_img.rows - Number; i++) 
	for (int j = 0; j < old_img.cols - Number; j++) 
	{ 
		randomNum = rng.uniform(0, Number); 
		new_img.at<Vec3b>(i, j)[0] = old_img.at<Vec3b>(i + randomNum, j + randomNum)[0]; 
		new_img.at<Vec3b>(i, j)[1] = old_img.at<Vec3b>(i + randomNum, j + randomNum)[1]; 
		new_img.at<Vec3b>(i, j)[2] = old_img.at<Vec3b>(i + randomNum, j + randomNum)[2]; 
	} 
}

void Image::_sketch()
{
	int width=old_img.cols;
	int heigh=old_img.rows;
	Mat gray0, gray1;
	//去色
	cvtColor(old_img,gray0,CV_BGR2GRAY);
	//反色
	addWeighted(gray0,-1,NULL,0,255,gray1);
	//高斯模糊,高斯核的Size与最后的效果有关
	GaussianBlur(gray1,gray1,Size(11,11),0);
 
	//融合：颜色减淡
	Mat img(gray1.size(),CV_8UC1);
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
	img.copyTo(new_img);
}

void Image::_oilPaint()
{
	for(int j=0;j<old_img.rows-2;j++)
	{
		//const uchar*current=old_img.ptr<const uchar>(j);//当前行
		const uchar*next1=old_img.ptr<const uchar>(j+1);//后1行
		const uchar*next2=old_img.ptr<const uchar>(j+2);//后两行
		const uchar*next=next1;
		uchar *output=new_img.ptr<uchar>(j);
		for(int i=0;i<old_img.cols-2;++i)
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
}

void Image::_woodCut()
{ 
	for(int j=0;j<old_img.rows;j++)
	{
		const uchar*current=old_img.ptr<const uchar>(j);//当前行
		uchar *output=new_img.ptr<uchar>(j);
		for(int i=0;i<old_img.cols;++i)
		{
			if((current[3*i+0]+current[3*i+1]+current[3*i+2])/3>128)
				output[3*i+0]=output[3*i+1]=output[3*i+2]=0;
			else
		      output[3*i+0]=output[3*i+1]=output[3*i+2]=255;
		}
    }
}

void Image::_draw()
{
    int width=old_img.cols;
	int heigh=old_img.rows;
	Mat img(old_img.size(),CV_8UC3);
	for (int y=0; y<heigh; y++)
	{
		uchar* P0  = old_img.ptr<uchar>(y);
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
	cvtColor(img,new_img,CV_BGR2GRAY);
	normalize(new_img,new_img,255,0,CV_MINMAX);
}

void Image::_onTrackbar()
{
	int width=old_img.cols;
	int heigh=old_img.rows;
	angle = 0.0;
	
	for (int y=0; y<heigh; y++)
	{
		int changeX = A*sin(angle);
		uchar *srcP = old_img.ptr<uchar>(y);
		uchar *imgP = new_img.ptr<uchar>(y);
		for (int x=0; x<width; x++)
		{
			if(changeX+x<width && changeX+x>0)		//正弦分布（-1,1）
			{
				imgP[3*x]=srcP[3*(x+changeX)];
				imgP[3*x+1]=srcP[3*(x+changeX)+1];
				imgP[3*x+2]=srcP[3*(x+changeX)+2];
			}
			//每行开始和结束的空白区;
			else if(x<=changeX)       
			{
				imgP[3*x]=srcP[0];
				imgP[3*x+1]=srcP[1];
				imgP[3*x+2]=srcP[2];
			}
			else if (x>=width-changeX)
			{
				imgP[3*x]=srcP[3*(width-1)];
				imgP[3*x+1]=srcP[3*(width-1)+1];
				imgP[3*x+2]=srcP[3*(width-1)+2];
			}
		}
		angle += ((double)deltaI)/100;
	}
}

void Image::_freezing()
{
	int width=old_img.cols;
	int heigh=old_img.rows;
	Mat dst(old_img.size(),CV_8UC3);
	for (int y=0;y<heigh;y++)
	{
		uchar* imgP=old_img.ptr<uchar>(y);
		uchar* dstP=dst.ptr<uchar>(y);
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
    dst.copyTo(new_img);
}
void Image::_casting()
{
	int width=old_img.cols;
	int heigh=old_img.rows;
	Mat dst(old_img.size(),CV_8UC3);
	for (int y=0;y<heigh;y++)
	{
		uchar* imgP=old_img.ptr<uchar>(y);
		uchar* dstP=dst.ptr<uchar>(y);
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
    dst.copyTo(new_img);
}
