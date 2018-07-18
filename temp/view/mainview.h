#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <memory>
#include <QImage>
#include <QDebug>
#include <iostream>
#include <QLabel>
#include <QScrollArea>
#include <QJsonObject>
#include <QMouseEvent>
#include "../common/etlbase.h"
#include "./sinks/mainimagesink.h"

namespace UI {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT
public:
    MainView();
    ~MainView();

    void update();

    void setImage(std::shared_ptr<QImage>);
    void setOpenFileCommand(std::shared_ptr<ICommandBase>);
    void setSaveFileCommand(std::shared_ptr<ICommandBase>);

    std::shared_ptr<IPropertyNotification> getMainViewSink();

private slots:
    // file system operation

    // file
    void open();
    void saveAs();

private:
    void initializeViews();
    void initializeFileMenu();

    void updateActions();
    void mouseMoveEvent(QMouseEvent *e);

    UI::MainView *ui;
    std::shared_ptr<QImage> image;
    QLabel *imageLabel;
    QLabel *positionLabel;
    QLabel *pixelColorLabel;
    QLabel *pixelRGBLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    //QMenu
    //...

    QAction *saveAsAct;

    std::shared_ptr<ICommandBase> openFileCommand;
    std::shared_ptr<ICommandBase> saveFileCommand;

    std::shared_ptr<MainImageSink> mainViewSink;
};

#endif // MAINVIEW_H
