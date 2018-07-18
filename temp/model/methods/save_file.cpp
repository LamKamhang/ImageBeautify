#include "../model.h"

void Model::save_file(const std::string &path) throw()
{
    showImg.copyTo(originImg);
    cv::imwrite(path, showImg);
}
