#include "model.h"


const cv::Mat& Model::getMain()
{
    return mainImg;
}

const cv::Mat& Model::getSub()
{
    return subImg;
}

bool Model::open_file(const std::string &path)
{
    originImg = cv::imread(path);
    if (originImg.empty())
    {
        return false;
    }
    else
    {
        originImg.copyTo(mainImg);
        Fire_OnPropertyChanged(MAIN_IMAGE);
    }
}

bool Model::open_sub_file(const std::string &path)
{
    tmpImg = cv::imread(path);
    if (tmpImg.empty())
    {
        return false;
    }
    else
    {
        tmpImg.copyTo(subImg);
        Fire_OnPropertyChanged(SUB_IMAGE);
        return true;
    }
}

bool Model::save_file(const std::string &path)
{
    if (mainImg.empty())
    {
        return false;
    }
    else
    {
        mainImg.copyTo(originImg);
        cv::imwrite(path, mainImg);
        return true;
    }
}

bool Model::sub2main()
{
    if (subImg.empty())
    {
        return false;
    }
    else
    {
        subImg.copyTo(mainImg);
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::origin2main()
{
    if (originImg.empty())
    {
        return false;
    }
    else
    {
        originImg.copyTo(mainImg);
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::main2sub()
{
    if (mainImg.empty())
    {
        return false;
    }
    else
    {
        mainImg.copyTo(subImg);
        Fire_OnPropertyChanged(SUB_IMAGE);
        return true;
    }
}
