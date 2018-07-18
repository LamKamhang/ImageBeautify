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
#include "Commands/command.h"

class Notification;

namespace UI{
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT
public:
    MainView();
    ~MainView();

    void update();

    void set_img(std::shared_ptr<QImage>);
    void set_open_file_command(std::shared_ptr<Command>);
    void set_save_file_command(std::shared_ptr<Command>);

    std::shared_ptr<Notification> get_update_mainview_notification();

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
    QLabel *imageLabel;
    QLabel *positionLabel;
    QLabel *pixelColorLabel;
    QLabel *pixelRGBLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

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

    std::shared_ptr<Command> open_file_command;
    std::shared_ptr<Command> save_file_command;

    std::shared_ptr<Notification> update_mainview_notification;
};

#endif // MAINVIEW_H
