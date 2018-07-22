#include "model.h"
#include <QImageReader>
#include <QImageWriter>
#include <QRgb>
#include "../common/util.h"

const QImage& Model::getMain()
{
    return mainImg;
}

const QImage& Model::getSub()
{
    return subImg;
}

bool Model::open_file(const QString &path)
{
    QImageReader reader(path);
    reader.setAutoTransform(true);
    originImg = reader.read();
    if (originImg.isNull())
    {
        return false;
    }
    else
    {
        mainImg = originImg.copy();
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::open_sub_file(const QString &path)
{
    QImageReader reader(path);
    reader.setAutoTransform(true);
    tmpImg = reader.read();
    if (tmpImg.isNull())
    {
        return false;
    }
    else
    {
        subImg = tmpImg.copy();
        Fire_OnPropertyChanged(SUB_IMAGE);
        return true;
    }
}

bool Model::save_file(const QString &path)
{
    if (mainImg.isNull())
    {
        return false;
    }
    else
    {
        QImageWriter writer(path);
        if (writer.write(mainImg))
        {
            originImg = mainImg.copy();
            return true;
        }else
            return false;
    }
}

bool Model::sub2main()
{
    if (subImg.isNull())
    {
        return false;
    }
    else
    {
        mainImg = subImg.copy();
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::origin2main()
{
    if (originImg.isNull())
    {
        return false;
    }
    else
    {
        mainImg = originImg.copy();
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::main2sub()
{
    if (mainImg.isNull())
    {
        return false;
    }
    else
    {
        subImg = mainImg.copy();
        Fire_OnPropertyChanged(SUB_IMAGE);
        return true;
    }
}

bool Model::sub2tmp()
{
    if (subImg.isNull())
    {
        return false;
    }
    else
    {
        tmpImg = subImg.copy();
        return true;
    }
}

bool Model::mix_tmp_main(int alpha)
{
    if (mainImg.height() != tmpImg.height() ||
            mainImg.width() != tmpImg.width())
    {
        return false;
    }
    else
    {
        // QRgb value;
        // subImg = mainImg.copy();
        // double dalpha = alpha * 1.0 / 100.0;
        // int height = mainImg.height();
        // int width = mainImg.width();
        // for (int i = 0; i < height; ++i)
        // {
        //     for (int j = 0; j < width; ++j)
        //     {
        //         value = mainImg.color(i*width + j)*(1-dalpha) + tmpImg.color(i*width + j)*dalpha;
        //         subImg.setPixel(i, j, value);
        //     }
        // }
        double dalpha = alpha * 1.0 / 100.0;
        cv::Mat src1 = Tools::QImage2Mat(mainImg);
        cv::Mat src2 = Tools::QImage2Mat(tmpImg);
        cv::Mat dst;
        cv::addWeighted(src1, 1 - dalpha, src2, dalpha, 0.0, dst);
        subImg = Tools::Mat2QImage(dst);
        Fire_OnPropertyChanged(SUB_IMAGE);
        return true;
    }
}
