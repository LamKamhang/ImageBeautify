#include "lemo_effect.h"

using namespace cv;
using namespace std;

void LemoEffect::_nostalgia(const cv::Mat &scr,cv::Mat &dst)
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

void LemoEffect::_BlackComic(const cv::Mat &scr,cv::Mat &dst)
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

void LemoEffect::_timetuunel(const cv::Mat &scr,cv::Mat &dst)
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

void LemoEffect::_classiclomo(const cv::Mat &scr,cv::Mat &dst)
{
    Mat image= scr.clone();
    Mat new_image = Mat::zeros( image.size(), image.type() );
    for( int y = 0; y < image.rows; y++ )
    {
        for( int x = 0; x < image.cols; x++ )
        {
                new_image.at<Vec3b>(y,x)[0] =  10*sqrt(image.at<Vec3b>(y,x)[0]);
                new_image.at<Vec3b>(y,x)[1] = image.at<Vec3b>(y,x)[1];
                new_image.at<Vec3b>(y,x)[2] =  image.at<Vec3b>(y,x)[2];
        }
    }
    Mat mergeImg;
    vector<Mat> splitBGR(image.channels());
    split(image,splitBGR);
    for(int i=0; i<image.channels(); i++)
        equalizeHist(splitBGR[i],splitBGR[i]);
    merge(splitBGR,mergeImg);
    Mat blur_image = Mat::zeros( image.size(), image.type() );
    blur(new_image,blur_image,Size( 8, 8), Point(-1,-1),BORDER_DEFAULT);
    Mat src=image;
    Mat res,roi,reverse_roi,reverse_res;
    res=Mat::zeros( image.size(), image.type() );
    reverse_res=Mat::zeros( image.size(), image.type() );
    roi=Mat::zeros( image.size(), image.type());
    reverse_roi=Mat(image.size(),image.type());
    for( int y = 0; y < reverse_roi.rows; y++ )
    {
        for( int x = 0; x < reverse_roi.cols; x++ )
        {
                reverse_roi.at<Vec3b>(y,x)[0] =	255;
                reverse_roi.at<Vec3b>(y,x)[1] = 255;
                reverse_roi.at<Vec3b>(y,x)[2] = 255;
        }
    }
    int thickness = 2;
    int lineType = 8;
    double angle=90;
    double w=image.rows;
    ellipse( roi,

           Point( image.cols/2, image.rows/2 ),

           Size( image.cols/3.0, image.rows/2.0 ),

           angle,

           0,

           360,

           Scalar( 255, 255, 255 ),

           thickness,

           lineType );

    ellipse(reverse_roi, Point( image.cols/2, image.rows/2 ), Size( image.cols/4.0, image.rows/2.0 ), angle,0,360,Scalar( 0, 0, 0 ),thickness,lineType );
    floodFill(reverse_roi, Point(w/2, w/2), Scalar( 0, 0, 0 ));
    floodFill(roi, Point(w/2, w/2), Scalar( 255, 255, 255 ));
    image.copyTo(res,roi);
    image.copyTo(reverse_res,reverse_roi);
    cvtColor(res,res,CV_BGR2HSV);
    for( int y = 0; y < res.rows; y++ )
    {
        for( int x = 0; x < res.cols; x++ )
        {
                res.at<Vec3b>(y,x)[1] = res.at<Vec3b>(y,x)[1];
                res.at<Vec3b>(y,x)[2] = res.at<Vec3b>(y,x)[2];
        }
    }
    cvtColor(res,res,CV_HSV2BGR);
    cvtColor(reverse_res,reverse_res,CV_BGR2HSV);
    for( int y = 0; y < reverse_res.rows; y++ )
    {
        for( int x = 0; x < reverse_res.cols; x++ )
        {
                reverse_res.at<Vec3b>(y,x)[1] = 1.5*reverse_res.at<Vec3b>(y,x)[1];
                if(reverse_res.at<Vec3b>(y,x)[1]>255)
                {
                    reverse_res.at<Vec3b>(y,x)[1]=255;
                }
                reverse_res.at<Vec3b>(y,x)[2] = reverse_res.at<Vec3b>(y,x)[2];
        }
    }
    cvtColor(reverse_res,reverse_res,CV_HSV2BGR);
    reverse_res=reverse_res+res;
    for( int y = 0; y < image.rows; y++ )
    {
        for( int x = 0; x < image.cols; x++ )
        {

                reverse_res.at<Vec3b>(y,x)[0] =  10*sqrt(reverse_res.at<Vec3b>(y,x)[0]);
                reverse_res.at<Vec3b>(y,x)[1] = reverse_res.at<Vec3b>(y,x)[1];
                reverse_res.at<Vec3b>(y,x)[2] =  reverse_res.at<Vec3b>(y,x)[2];
        }
    }
    blur(reverse_res,reverse_res,Size( 2, 2), Point(-1,-1),BORDER_DEFAULT);
    dst = reverse_res.clone();
}
