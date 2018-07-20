#include "lemo_effect.h"

using namespace cv;
using namespace std;

void _nostalgia(const cv::Mat &scr,cv::Mat &dst)
{

    int rowNum = scr.rows;
    int colNum = scr.cols;
    dst = scr.clone();
    for(int j = 0;j<rowNum;j++){
        uchar* data = dst.ptr<uchar>(j);
        for(int i = 0;i<colNum;i++){
            int b = data[i*3];
            int g = data[i*3+1];
            int r = data[i*3+2];

            int R = static_cast<int>(0.393*r + 0.769*g + 0.189*b);
            int G = static_cast<int>(0.349*r + 0.686*g + 0.168*b);
            int B = static_cast<int>(0.272*r + 0.534*g + 0.131*b);

            data[i*3+2] = max(0,min(R,255));
            data[i*3+1] = max(0,min(G,255));
            data[i*3] = max(0,min(B,255));
        }
    }
}

void _BlackComic(const cv::Mat &scr,cv::Mat &dst)
{
    int rowNum = scr.rows;
     int colNum = scr.cols;
     dst = scr.clone();

     for(int j = 0;j<rowNum;j++){
         uchar* data = dst.ptr<uchar>(j);
         for(int i = 0;i<colNum;i++){
             int b = data[i*3];
             int g = data[i*3+1];
             int r = data[i*3+2];

             int R = (abs(2*g-b+r)*r)>>8;
             int G = (abs(2*b-g+r)*r)>>8;
             int B = (abs(2*b-g+r)*r)>>8;

             R = max(0,min(R,255));
             G = max(0,min(G,255));
             B = max(0,min(B,255));

             int gray = (R+G+B)/3;

             R = min(255,gray + 10);

             data[i*3+2] = R;
             data[i*3+1] = R;
             data[i*3] = gray;
         }
     }
}

void _timetuunel(const cv::Mat &scr,cv::Mat &dst)
{
Mat Img_in = scr.clone();


Mat temp = Img_in.clone();

Point center(Img_in.cols/2,Img_in.rows/2);



Mat Img_out(Img_in.size(), CV_32FC3);

Img_in.convertTo(Img_out, CV_32FC3);



int width=Img_in.cols;

int height=Img_in.rows;



float R;

float angle;



Point Center(width/2, height/2);

float t1, t2, t3;

int new_x, new_y;



int Num=20;



for (int y=0; y<height; y++)

{

    for (int x=0; x<width; x++)

    {

        t1=0; t2=0; t3=0;

        R=sqrt((y-Center.y)*(y-Center.y)+(x-Center.x)*(x-Center.x));

        angle=atan2((float)(y-Center.y), (float)(x-Center.x));

        for (int mm=0; mm<Num; mm++)

        {

            float tmR=R-mm>0 ? R-mm : 0.0;



            new_x=tmR*cos(angle)+Center.x;

            new_y=tmR*sin(angle)+Center.y;



            if(new_x<0)       new_x=0;

            if(new_x>width-1) new_x=width-1;

            if(new_y<0)       new_y=0;

            if(new_y>height-1)new_y=height-1;



            t1=t1+Img_in.at<Vec3b>(new_y, new_x)[0];

            t2=t2+Img_in.at<Vec3b>(new_y, new_x)[1];

            t3=t3+Img_in.at<Vec3b>(new_y, new_x)[2];



        }



        Img_out.at<Vec3f>(y, x)[0]=t1/Num;

        Img_out.at<Vec3f>(y, x)[1]=t2/Num;

        Img_out.at<Vec3f>(y, x)[2]=t3/Num;



    }

}

int radius = min(temp.cols,temp.rows);
radius = radius / 3;
for ( int x = 0; x < temp.cols; x++)

{

    for ( int y = 0; y < temp.rows; y++)

    {

        int m = ((x - center.x) * (x - center.x) + (y - center.y) *(y - center.y));

        if (m < (radius * radius))

        {

            Img_out.at<Vec3f>(Point(x, y))[0] = temp.at<Vec3b>(Point(x, y))[0];

            Img_out.at<Vec3f>(Point(x, y))[1] = temp.at<Vec3b>(Point(x, y))[1];

            Img_out.at<Vec3f>(Point(x, y))[2] = temp.at<Vec3b>(Point(x, y))[2];

        }

    }
}



Img_out=Img_out/255.0;



waitKey();


}
