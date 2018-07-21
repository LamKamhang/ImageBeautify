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
#include "./sinks/maincommandsink.h"
#include "../view/filterdialog.h"
#include "../view/edgedetectiondialog.h"
#include "../view/houghcircledetectiondialog.h"
#include "../view/dualthresholddialog.h"
#include "../view/huesaturalightdialog.h"
#include "../view/curvedialog.h"
#include "../view/leveldialog.h"
#include "../view/clipdialog.h"
#include "../view/scaledialog.h"
#include "../view/histogramdialog.h"
#include "../view/algebraicdialog.h"
#include "../view/binarymorphologydialog.h"
#include "../view/graymorphologydialog.h"

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
    void updateLogManager();

    void setImage(std::shared_ptr<QImage>);
    void setSubImage(std::shared_ptr<QImage>);
    void setUndoEnabled(std::shared_ptr<bool>);
    void setRedoEnabled(std::shared_ptr<bool>);
    void setUndoMsg(std::shared_ptr<QString>);
    void setRedoMsg(std::shared_ptr<QString>);
    void setIsBinary(std::shared_ptr<bool>);
    void setIsGray(std::shared_ptr<bool>);

    void setOpenFileCommand(std::shared_ptr<ICommandBase>);
    void setSaveFileCommand(std::shared_ptr<ICommandBase>);
    void setOpenSubDialogCommand(std::shared_ptr<ICommandBase>);
    void setOpenSubFileCommand(std::shared_ptr<ICommandBase>);
    void setUndoCommand(std::shared_ptr<ICommandBase>);
    void setRedoCommand(std::shared_ptr<ICommandBase>);

    void setFilterCommand(std::shared_ptr<ICommandBase>);
    void setEdgeDetectionCommand(std::shared_ptr<ICommandBase>);
    void setHoughCircleDetectionCommand(std::shared_ptr<ICommandBase>);
    void setChannelCommand(std::shared_ptr<ICommandBase>);
    void setGrayScaleTransferCommand(std::shared_ptr<ICommandBase>);
    void setOtsuCommand(std::shared_ptr<ICommandBase>);
    void setHoughLineDetectionCommand(std::shared_ptr<ICommandBase>);
    void setDualThresholdCommand(std::shared_ptr<ICommandBase>);
    void setHueSaturaLightCommand(std::shared_ptr<ICommandBase>);
    void setCurveCommand(std::shared_ptr<ICommandBase>);
    void setLevelCommand(std::shared_ptr<ICommandBase>);
    void setClipCommand(std::shared_ptr<ICommandBase>);
    void setScaleCommand(std::shared_ptr<ICommandBase>);
    void setHistogramCommand(std::shared_ptr<ICommandBase>);
    void setAlgebraicCommand(std::shared_ptr<ICommandBase>);
    void setBinaryMorphologyCommand(std::shared_ptr<ICommandBase>);
    void setGrayMorphologyCommand(std::shared_ptr<ICommandBase>);

    std::shared_ptr<IPropertyNotification> getMainViewSink();
    std::shared_ptr<ICommandNotification> getMainCommandSink();

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
    void receiveApplyHueSaturaLight(std::shared_ptr<JsonParameters>);
    void receiveApplyCurve(std::shared_ptr<JsonParameters>);
    void receiveApplyLevel(std::shared_ptr<JsonParameters>);
    void receiveApplyClip(std::shared_ptr<JsonParameters>);
    void receiveApplyScale(std::shared_ptr<JsonParameters>);
    void receiveApplyHistogram(std::shared_ptr<VectorParameters<int> >);
    void receiveApplyAlgebraic(std::shared_ptr<JsonParameters>);
    void receiveAlgebraicOpenFileImage2(QString);
    void receiveApplyBinaryMorphology(std::shared_ptr<JsonParameters>);
    void receiveApplyGrayMorphology(std::shared_ptr<JsonParameters>);

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
    // view log property
    std::shared_ptr<bool> undoEnabled;
    std::shared_ptr<bool> redoEnabled;
    std::shared_ptr<QString> undoMsg;
    std::shared_ptr<QString> redoMsg;
    // image property
    std::shared_ptr<bool> isBinary;
    std::shared_ptr<bool> isGray;

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
    std::shared_ptr<ICommandBase> openSubFileCommand;
    std::shared_ptr<ICommandBase> undoCommand;
    std::shared_ptr<ICommandBase> redoCommand;

    std::shared_ptr<ICommandBase> filterCommand;
    std::shared_ptr<ICommandBase> edgeDetectionCommand;
    std::shared_ptr<ICommandBase> houghCircleDetectionCommand;
    std::shared_ptr<ICommandBase> channelCommand;
    std::shared_ptr<ICommandBase> grayScaleTransferCommand;
    std::shared_ptr<ICommandBase> otsuCommand;
    std::shared_ptr<ICommandBase> houghLineDetectionCommand;
    std::shared_ptr<ICommandBase> dualThresholdCommand;
    std::shared_ptr<ICommandBase> hueSaturaLightCommand;
    std::shared_ptr<ICommandBase> curveCommand;
    std::shared_ptr<ICommandBase> levelCommand;
    std::shared_ptr<ICommandBase> clipCommand;
    std::shared_ptr<ICommandBase> scaleCommand;
    std::shared_ptr<ICommandBase> histogramCommand;
    std::shared_ptr<ICommandBase> algebraicCommand;
    std::shared_ptr<ICommandBase> binaryMorphologyCommand;
    std::shared_ptr<ICommandBase> grayMorphologyCommand;


    std::shared_ptr<MainImageSink> mainViewSink;
    std::shared_ptr<MainCommandSink> mainCommandSink;
};

#endif // MAINVIEW_H
