#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <memory>
#include <QImage>
#include <QDebug>
#include <iostream>
#include <QLabel>
#include <QScrollArea>
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

    QAction *saveAsAct;

    std::shared_ptr<Command> open_file_command;
    std::shared_ptr<Command> save_file_command;

    std::shared_ptr<Notification> update_mainview_notification;
};

#endif // MAINVIEW_H
