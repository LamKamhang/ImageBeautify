#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDragEnterEvent>
#include "imagecontainer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    ImageContainer ImageManager;
    QVector<int> ImageIDs;
//    void dragEnterEvent(QDragEnterEvent * event);
//    void dropEvent(QDropEvent *event);

private slots:
    void on_actionnew_file_N_triggered();
    void on_actiontool_box_T_triggered();
    void tool_box_T_2_dockWidget();
    void on_actionbaocun_S_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
