#include "util.h"
#include <QImageReader>
#include <QImageWriter>
#include <QDebug>
#define _PATH_  "Cache/img.jpg"

QImage Tools::Mat2QImage(const cv::Mat & src)
{
     qDebug()<<"Mat2QImage";
     cv::imwrite(_PATH_, src);
     QImageReader reader(_PATH_);
     reader.setAutoTransform(true);
     return reader.read();
}

cv::Mat Tools::QImage2Mat(const QImage& src)
{
    qDebug()<<"QImage2Mat";
    QImageWriter writer(_PATH_);
    if (writer.write(src))
    {
        qDebug()<<"QImage2Mat true";
        return  cv::imread(_PATH_);
    }
    else {
        qDebug()<<"QImage2Mat false";
        return cv::Mat();
    }
}


//cv::Mat Tools::QImage2Mat(const QImage &rhs)
//{
//    cv::Mat mat;
//    switch (rhs.format())
//    {
//    case QImage::Format_ARGB32:
//    case QImage::Format_RGB32:
//    case QImage::Format_ARGB32_Premultiplied:
//        mat = cv::Mat(rhs.height(), rhs.width(), CV_8UC4, (void*)rhs.constBits(), rhs.bytesPerLine());
//        break;
//    case QImage::Format_RGB888:
//        mat = cv::Mat(rhs.height(), rhs.width(), CV_8UC3, (void*)rhs.constBits(), rhs.bytesPerLine());
//        cv::cvtColor(mat, mat, CV_BGR2RGB);
//        break;
//    case QImage::Format_Indexed8:
//        mat = cv::Mat(rhs.height(), rhs.width(), CV_8UC1, (void*)rhs.constBits(), rhs.bytesPerLine());
//        break;
//    }
//    return mat;
//}

//QImage Tools::Mat2QImage(const cv::Mat& rhs)
//{
//    // 8-bits unsigned, NO. OF CHANNELS = 1
//    if(rhs.type() == CV_8UC1)
//    {
////        qDebug() << "CV_8UC1";
//        QImage image(rhs.cols, rhs.rows, QImage::Format_Indexed8);
//        // Set the color table (used to translate colour indexes to qRgb values)
//        image.setColorCount(256);
//        for(int i = 0; i < 256; i++)
//        {
//            image.setColor(i, qRgb(i, i, i));
//        }
//        // Copy input Mat
//        uchar *pSrc = rhs.data;
//        for(int row = 0; row < rhs.rows; row ++)
//        {
//            uchar *pDest = image.scanLine(row);
//            memcpy(pDest, pSrc, rhs.cols);
//            pSrc += rhs.step;
//        }
//        return image;
//    }
//    // 8-bits unsigned, NO. OF CHANNELS = 3
//    else if(rhs.type() == CV_8UC3)
//    {
////        qDebug() << "CV_8UC3";
//        // Copy input Mat
//        const uchar *pSrc = (const uchar*)rhs.data;
//        // Create QImage with same dimensions as input Mat
//        QImage image(pSrc, rhs.cols, rhs.rows, rhs.step, QImage::Format_RGB888);
//        return image.rgbSwapped();
//    }
//    else if(rhs.type() == CV_8UC4)
//    {
////        qDebug() << "CV_8UC4";
//        // Copy input Mat
//        const uchar *pSrc = (const uchar*)rhs.data;
//        // Create QImage with same dimensions as input Mat
//        QImage image(pSrc, rhs.cols, rhs.rows, rhs.step, QImage::Format_ARGB32);
//        return image.copy();
//    }
//    else
//    {
////        qDebug() << "ERROR: Mat could not be converted to QImage.";
//        return QImage();
//    }
//}
