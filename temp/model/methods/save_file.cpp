#include "../model.h"

void Model::save_file(const std::string &path)
{
    showImg.copyTo(originImg);
    cv::imwrite(path, showImg);
}
