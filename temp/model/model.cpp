#include "model.h"

const cv::Mat& Model::getShow()
{
    return showImg;
}

const cv::Mat& Model::getOrigin()
{
    return originImg;
}

void Model::save_file(const std::string &path) throw()
{
    showImg.copyTo(originImg);
    cv::imwrite(path, showImg);
}

void Model::open_file(const std::string &path) throw(errorType)
{
    tmpImg = cv::imread(path);
    if(tmpImg.empty())
    {
        throw(CANNOT_OPEN_IMAGE);
    }
    else
    {
        tmpImg.copyTo(originImg);
        tmpImg.copyTo(showImg);
        Fire_OnPropertyChanged(MAIN_IMAGE);
    }
}
