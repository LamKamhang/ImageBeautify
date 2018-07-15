#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <QMdiSubWindow>
#include <QImage>
#include <QString>
#include <QMap>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "savedialog.h"
#include "tools.h"
#include <QFileDialog>
#include <QApplication>
using namespace cv;
using namespace std;

class Photo{
private:
   QString path;
   QImage* image;
   Mat* mat;
   bool isSaved;
   bool isEdited;
   bool isFoucsed;
   bool enabled;
public:
    Photo(const QString &path=""){
        QImage* img =  new QImage(path);
            if(img){
                this->path = path;
                image = img;
                mat = new class Mat(Tools::QImageToMat(*img));
                enabled = true;
            }
        else{
            this->path = "";
            image = NULL;
            mat = NULL;
            enabled = false;
        }
        isSaved = true;
        isEdited = false;
        isFoucsed = false;
    }
    QImage* Image(){
        return image;
    }
    Mat* Mat(){
        return mat;
    }
    bool IsSaved(){
        return isSaved;
    }
    bool IsEdited(){
        return isEdited;
    }
    bool IsFoucsed(){
        return isFoucsed;
    }
    bool IsEnabled(){
        return enabled;
    }
    void setEnabled(bool e){
        enabled = e;
    }
    void setSaved(bool s){
        isSaved = s;
        if(isSaved)isEdited = false;
    }
    void setEdited(bool e){
        isEdited = e;
        if(isEdited)isSaved = false;
    }
    void setFoucsed(bool f){
        isFoucsed = f;
    }
};

class ImageManager{
private:
    QVector<QString> savedPhotoPaths;
    QVector<Photo*> photos;
    Photo* curphoto;
    Ui::MainWindow *ui;
public:
    ImageManager(Ui::MainWindow *ui){
        this->ui = ui;
        savedPhotoPaths.clear();
        photos.clear();
        curphoto = NULL;
    }

    Photo*& getCurPhoto(){
        return curphoto;
    }

    void openImage(const QString& path,bool usePath){
        if(curphoto && curphoto->IsEnabled() && curphoto->IsEdited()){
            SaveDialog sdlg;
            sdlg.exec();
            switch (sdlg.state) {
            case SaveDialog::NOT_SAVE:

                break;
            case SaveDialog::SAVE:
                break;
            case SaveDialog::CANCEL:
                break;
            default:
                break;
            }
            qDebug()<<"sdlg.state == SaveDialog::NOT_SAVE" << (sdlg.state == SaveDialog::NOT_SAVE);
        }
        else{
            Photo * oldimg = curphoto;
            if(usePath)curphoto = new Photo(path);
            else{
//                QString filename = QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
//                curphoto = new Photo(filename);
            }
            if(oldimg)delete oldimg;
        }
    }

    QLabel* showImage(){
        if(!curphoto)return NULL;

        QLabel *imageLabel = new QLabel;
        imageLabel->setAlignment(Qt::AlignCenter);
        QImage * img = curphoto->Image();

        imageLabel->setPixmap(QPixmap::fromImage(*img));
        imageLabel->setAttribute(Qt::WA_DeleteOnClose);
        ui->imageGround->setBackgroundRole(QPalette::Dark);
        ui->imageGround->setWidgetResizable(true);
        ui->imageGround->setAlignment(Qt::AlignCenter);
        ui->imageGround->setWidget(imageLabel);
        return imageLabel;
    }

    bool saveImage(const QString& path){
        if(!curphoto || !curphoto->IsEnabled())return false;
        return curphoto->Image()->save(path);
    }
};

#endif // IMAGECONTAINER_H
