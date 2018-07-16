#ifndef PHOTOSHOPGUI_H
#define PHOTOSHOPGUI_H

#include <QMainWindow>
#include <QImage>
#include <QJsonObject>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif
#include <QMouseEvent>
#include "../model/log.h"
#include "../model/imageoperations.h"
#include "../view/algebraicdialog.h"
#include "../view/huesaturalightdialog.h"
#include "../view/dualthresholddialog.h"
#include "../view/scaledialog.h"
#include "../view/filterdialog.h"
#include "../view/edgedetectiondialog.h"
#include "../view/houghtransformdialog.h"
#include "../view/clipdialog.h"
#include "../view/binarymorphodialog.h"
#include "../view/graymorphodialog.h"
#include "../view/curvedialog.h"
#include "../view/histogramdialog.h"
#include "../view/leveldialog.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QStackedLayout;
QT_END_NAMESPACE

class PhotoshopGUI : public QMainWindow
{
    Q_OBJECT

public:
    PhotoshopGUI();

private slots:
    void open();
    void saveAs();
    void print();
    void undo();
    void redo();
    void copy();
    void paste();
    void algebraic();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void redChannel();
    void greenChannel();
    void blueChannel();
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

    void receiveApplyAlgebraicOperation(QJsonObject, QImage);
    void receiveApplyHSLAdjust(QJsonObject, QImage);
    void receiveApplyDualThreshold(QJsonObject, QImage);
    void receiveApplyScale(QJsonObject);
    void receiveApplyFilter(QJsonObject);
    void receiveApplyEdgeDetection(QJsonObject);
    void receiveApplyHoughTransform(QJsonObject);
    void receiveApplyClip(QJsonObject);
    void receiveApplyBinaryMorpho(QJsonObject);
    void receiveApplyGrayMorpho(QJsonObject);
    void receiveApplyCurve(QJsonObject, QImage);
    void receiveApplyHistoEqualize(QImage);
    void receiveApplyLevelAdjust(QImage);

private:
    Log *log;
    ImageOperations *imageOperation;

    void initializeViews();
    void initializeFileMenu();
    void initializeEditMenu();
    void initializeImageMenu();
    void initializeViewMenu();
    void initializeAboutMenu();
    void updateActions();
    void updateCommitManager();
    void makeCommit(QImage image, QString operation);
    void clearLog();
    void mouseMoveEvent(QMouseEvent *e);

    bool loadFile(const QString &);
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);
    void updateImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QLabel *imageLabel;
    QLabel *positionLabel;
    QLabel *pixelColorLabel;
    QLabel *pixelRGBLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QMenu *imageMenu;

    QAction *saveAsAct;
    QAction *printAct;
    QAction *copyAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *undoAct;
    QAction *redoAct;
};

#endif // PHOTOSHOPGUI_H
