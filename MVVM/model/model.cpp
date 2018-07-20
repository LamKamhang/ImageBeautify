#include "model.h"
#include <QImageReader>
#include <QImageWriter>

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
        QImage tmp(originImg);
		mainImg = tmp;
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
        QImage tmp(tmpImg);
		subImg = tmp;
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
            QImage tmp(mainImg);
		    originImg = tmp;
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
        QImage tmp(subImg);
		mainImg = tmp;
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
        QImage tmp(originImg);
		mainImg = tmp;
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
        QImage tmp(mainImg);
		subImg = tmp;
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
        QImage tmp(subImg);
        tmpImg = tmp;
        // Fire_OnPropertyChanged(TMP_IMAGE);
        return true;
    }
}