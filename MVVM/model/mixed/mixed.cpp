#include "mixed.h"

using namespace std;

cv::Mat Mixed::_Hybrid(const cv::Mat &scr, const cv::Mat &dst, int pro)
{
    cv::Mat temp;
    double dpro = double(pro) / 100.0;
    cv::addWeighted(scr, 1.0 - dpro, dst, dpro, 0.0, temp);
    return temp;
}
