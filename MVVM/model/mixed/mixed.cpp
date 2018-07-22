#include "mixed.h"

using namespace std;

cv::Mat Mixed::_Hybrid(const cv::Mat &scr, const cv::Mat &dst, int pro)
{
    cv::Mat temp;
    cv::addWeighted(scr,1-pro,dst,pro,0.0,temp);
    return temp;
}
