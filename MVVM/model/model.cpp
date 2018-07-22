#include "model.h"
#include <QImageReader>
#include <QImageWriter>
#include <QDebug>

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
        qDebug() << "in model open file " << path;
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
        // Fire_OnPropertyChanged(TMP_IMAGE);
        return true;
    }
}
