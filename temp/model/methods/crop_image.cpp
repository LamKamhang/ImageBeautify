#include "../model.h"


void Model::crop(int x1, int y1, int x2, int y2)
{
    if (originImg.empty())
    {
        throw(EMPTY_IMAGE);
    }

    cv::Point point1(x1, y1);
    cv::Point point2(x2, y2);
    cv::Rect rect(point1, point2);
	
    //计算剪切区域：剪切Rect与源图像所在Rect的交集
	cv::Rect srcRect;
	srcRect = cv::Rect(0, 0, showImg.cols, showImg.rows);

    rect = rect & srcRect;

    if ( rect.width <= 0  || rect.height <= 0 )
    {
        throw(ILLEAGL_REGION);
    }

    //创建结果图像
    showImg.copyTo(tmpImg);
    tmpImg.create(cvSize(rect.width, rect.height), tmpImg.type());

    //复制源图像的剪切区域到结果图像
    tmpImg(rect).copyTo(showImg);
    Fire_OnPropertyChanged(MAIN_IMAGE);
}