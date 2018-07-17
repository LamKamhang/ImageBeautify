#include "transportmandq.h"
#include <qdebug.h>

Mat QimagetoMat(QImage P)
{
    Mat mat;
    qDebug() << P.format();
    switch(P.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(P.height(),P.width(),CV_8UC4,(void*)P.constBits(),P.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(P.height(),P.width(),CV_8UC3,(void*)P.constBits(),P.bytesPerLine());
        cv::cvtColor(mat,mat,CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(P.height(),P.width(),CV_8UC1,(void*)P.constBits(),P.bytesPerLine());
        break;
    }
    return mat;
}

QImage MattoQimage(Mat P)
{
    if(P.type()==CV_8UC1)
    {
        QImage image(P.cols,P.rows,QImage::Format_Indexed8);
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i,qRgb(i,i,i));
        }
        uchar *pSrc = P.data;
        for(int row = 0; row < P.rows ; row++)
        {
            uchar * pDest = image.scanLine(row);
            memcpy(pDest,pSrc,P.cols);
            pSrc += P.step;
        }
        return image;
    }
    else if(P.type()==CV_8UC3)
    {
        const uchar *pSrc = (const uchar*)P.data;
        QImage image(pSrc,P.cols,P.rows,P.step,QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(P.type()==CV_8UC3)
    {
        qDebug() << "ERROR: Mat could not be converted to Qimage.";
        return QImage();
    }
}
