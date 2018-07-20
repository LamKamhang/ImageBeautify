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
