#include "../model.h"

void Model::open_file(const std::string &path)
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
        Fire_OnPropertyChanged("MAIN_IMAGE");
    }
}