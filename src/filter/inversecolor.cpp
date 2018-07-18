#include "inversecolor.h"

Mat InverseColor::InverseColor(Mat P)//反色
{
    Mat img;

    int rowNum = mat.rows;
    int colNum = mat.cols*mat.channels();

    Mat temp;

    temp = img.clone();

    for(int j = 0; j < rowNum ; j++){
        uchar * row = temp.ptr<uchar>(j);
        for(int i = 0;i<colNum;i++){
            row[i] = 255 - row[i];
        }
    }
    return temp;
}
