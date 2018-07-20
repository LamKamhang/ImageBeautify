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
#include "../view/filterdialog.h"
#include "../view/edgedetectiondialog.h"
#include "../view/houghcircledetectiondialog.h"
#include "../view/dualthresholddialog.h"

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
    void updateSubImage();

    void setImage(std::shared_ptr<QImage>);
    void setSubImage(std::shared_ptr<QImage>);

    void setOpenFileCommand(std::shared_ptr<ICommandBase>);
    void setSaveFileCommand(std::shared_ptr<ICommandBase>);
    void setOpenSubDialogCommand(std::shared_ptr<ICommandBase>);

    void setFilterCommand(std::shared_ptr<ICommandBase>);
    void setEdgeDetectionCommand(std::shared_ptr<ICommandBase>);
    void setHoughCircleDetectionCommand(std::shared_ptr<ICommandBase>);
    void setChannelCommand(std::shared_ptr<ICommandBase>);
    void setGrayScaleTransferCommand(std::shared_ptr<ICommandBase>);
    void setOtsuCommand(std::shared_ptr<ICommandBase>);
    void setHoughLineDetectionCommand(std::shared_ptr<ICommandBase>);


    std::shared_ptr<IPropertyNotification> getMainViewSink();

signals:
    void subImageChanged();

private slots:
    // file system operation

    // file
    void open();
    void saveAs();
    // edit
    void undo();
    void redo();
    void copy();
    void paste();
    // view
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    // about
    void about();

    // basic operation
    void redChannel();
    void greenChannel();
    void blueChannel();
    void algebraic();
    void grayScaleTransfer();
    void hueSaturationLightness();
    void otsu();
    void dualThreshold();
    void clip();
    void scale();
    void filter();
    void edgeDetection();
    void houghLineDetect();
    void houghCircleDetect();
    void binaryMorphology();
    void grayMorphology();
    void curve();
    void histogram();
    void level();

    // basic operation receiver
    void receiveApplyFilter(std::shared_ptr<JsonParameters>);
    void receiveApplyEdgeDetection(std::shared_ptr<JsonParameters>);
    void receiveApplyHoughCircleDetection(std::shared_ptr<JsonParameters>);
    void receiveApplyDualThreshold(std::shared_ptr<JsonParameters>);

    // special effects
    void hotSpecialEffects();
    void basicSpecialEffects();
    void lomoSpecialEffects();
    void humanFaceSpecialEffects();
    void fashionSpecialEffects();
    void artSpecialEffects();

    // frame
    void colorfulFrame();
    void simpleFrame();
    void textureFrame();
    void tearFrame();
    void relaxedFrame();

private:
    void initializeViews();
    void initializeFileMenu();
    void initializeEditMenu();
    void initializeToolsMenu();
    void initializeSpecialEffectsMenu();
    void initializeFrameMenu();
    void initializeViewMenu();
    void initializeAboutMenu();

    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    void updateActions();
    void mouseMoveEvent(QMouseEvent *e);

    UI::MainView *ui;
    std::shared_ptr<QImage> image;
    std::shared_ptr<QImage> subimage;
    QLabel *imageLabel;
    QLabel *positionLabel;
    QLabel *pixelColorLabel;
    QLabel *pixelRGBLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    //QMenu
    QMenu *toolsMenu;
    QMenu *specialEffectsMenu;
    QMenu *frameMenu;

    QAction *saveAsAct;

    QAction *copyAct;

    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

    QAction *undoAct;
    QAction *redoAct;

    std::shared_ptr<ICommandBase> openFileCommand;
    std::shared_ptr<ICommandBase> saveFileCommand;
    std::shared_ptr<ICommandBase> openSubDialogCommand;

    std::shared_ptr<ICommandBase> filterCommand;
    std::shared_ptr<ICommandBase> edgeDetectionCommand;
    std::shared_ptr<ICommandBase> houghCircleDetectionCommand;
    std::shared_ptr<ICommandBase> channelCommand;
    std::shared_ptr<ICommandBase> grayScaleTransferCommand;
    std::shared_ptr<ICommandBase> otsuCommand;
    std::shared_ptr<ICommandBase> houghLineDetectionCommand;

    std::shared_ptr<MainImageSink> mainViewSink;
};

#endif // MAINVIEW_H
