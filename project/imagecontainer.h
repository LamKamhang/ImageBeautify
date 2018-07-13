#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <QMdiSubWindow>
#include <QImage>
#include <QString>
#include <QMap>
#include "tools.h"
using namespace cv;
using namespace std;

class ImageContainer{
private:
    QVector<QImage*> QImageContainer;
    QVector<Mat*> MatContainer;
    QMap<int,QMdiSubWindow*> ViewContainer;
    int curID;

public:
    ImageContainer(){
        QImageContainer.clear();
        MatContainer.clear();
        ViewContainer.clear();
        curID = 0;
    }

    QImage* getQImage(int ID){
        return QImageContainer[ID];
    }
    Mat* getMat(int ID){
        return MatContainer[ID];
    }
    QMdiSubWindow* getView(int ID){
        return ViewContainer[ID];
    }

    int loadQImage(const QString& path){
        QImage* newImg = new QImage(path);
        Mat* newMat = new Mat(Tools::QImageToMat(*newImg));
        QImageContainer.push_back(newImg);
        MatContainer.push_back(newMat);
        return curID++;
    }

    void bindView(int ID, QMdiSubWindow* view){
        ViewContainer.insert(ID, view);
    }

    void deleteImage(int ID){
        QImage* oldImg = QImageContainer[ID];
        Mat* oldMat = MatContainer[ID];
        delete oldImg;
        delete oldMat;
        QImageContainer[ID] = NULL;
        MatContainer[ID] = NULL;
        unbindView(ID);
    }

    void unbindView(int ID){
        auto key = ViewContainer.find(ID);
        if(key!=ViewContainer.end())
        {
            ViewContainer.erase(key);
        }
    }
};












#endif // IMAGECONTAINER_H
