#include "Include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QPixmap>
#include <QMovie>
#include <QToolButton>
#include <QSpinBox>
#include <QMdiSubWindow>
#include <QLabel>
#include <QTextEdit>
#include <QTextCursor>
#include <QDragEnterEvent>
#include <QUrl>
#include <QFile>
#include <QLabel>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QPainter>
#include <QTextStream>
#include <QDropEvent>
#include <QFileDialog>
#include <QDebug>
#include <QMimeData>
#include <QDrag>
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>
#include "Include/savedialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    imageManager(ui)
{
    ImageIDs.clear();
    ui->setupUi(this);
    ui->statusBar->showMessage(tr("欢迎使用图之美"),2000);
    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText(tr("Image Beautify"));
    ui->statusBar->addPermanentWidget(permanent);

    connect(ui->dockWidget,SIGNAL(visibilityChanged(bool)),this,SLOT(tool_box_T_2_dockWidget()));
    ui->imageGround->setAcceptDrops(true);
    setAcceptDrops(true);
//    ui->label->resize(512,512);
//    ui->label->setPixmap(QPixmap("images/image.png"));

//    QMovie *movie = new QMovie("/Users/huangwencan/gui/learn5/myMainWindow/images/image.png");
//    ui->label->setMovie(movie);
//    movie->start();
//    QMenu *editMenu = ui->menuBar->addMenu(tr("编辑(&E)"));
//    QAction *action_Open = editMenu->addAction(QIcon(":/myImage/images/image.png"),tr("打开文件(&O)"));
//    action_Open->setShortcut(QKeySequence("Ctrl+O"));
//    ui->mainToolBar->addAction(action_Open);

//    QActionGroup *group = new QActionGroup(this);
//    QAction *action_L = group->addAction(tr("左对齐(&L)"));
//    action_L->setCheckable(true);
//    QAction *action_R = group->addAction(tr("右对齐(&R"));
//    action_R->setCheckable(true);
//    QAction *action_C = group->addAction(tr("居中(&C"));
//    action_C->setCheckable(true);
//    action_L->setChecked(true);
//    editMenu->addSeparator();
//    editMenu->addAction(action_L);
//    editMenu->addAction(action_R);
//    editMenu->addAction(action_C);

//    QToolButton * toolBtn = new QToolButton(this);
//    toolBtn->setText(tr("颜色"));
//    QMenu *colorMenu = new QMenu(this);
//    colorMenu->addAction(tr("红色"));
//    colorMenu->addAction(tr("绿色"));
//    toolBtn->setMenu(colorMenu);
//    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
//    ui->mainToolBar->addWidget(toolBtn);

//    QSpinBox *spinBox = new QSpinBox(this);
//    ui->mainToolBar->addWidget(spinBox);

//    QAction *action_textTable = new QAction(tr("表格"),this);
//    QAction *action_textList = new QAction(tr("列表"),this);
//    QAction *action_textImage = new QAction(tr("图片"),this);
//    connect(action_textTable,SIGNAL(triggered()),this,SLOT(insertTable()));
//    connect(action_textList,SIGNAL(triggered()),this,SLOT(insertList()));
//    connect(action_textImage,SIGNAL(triggered()),this,SLOT(insertImage()));
//    ui->mainToolBar->addAction(action_textTable);
//    ui->mainToolBar->addAction(action_textList);
//    ui->mainToolBar->addAction(action_textImage);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){

        event->acceptProposedAction();
    }
    else event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl>urls = event->mimeData()->urls();
    if(urls.isEmpty())return;
    QString fileName = urls.first().toLocalFile();
    if(fileName.isEmpty())return;
    else{
        if(imageManager.getCurPhoto() && imageManager.getCurPhoto()->IsEnabled() && imageManager.getCurPhoto()->IsEdited()){
            SaveDialog sdlg;
            sdlg.exec();
        }
        else{
            Photo * oldimg = imageManager.getCurPhoto();
            imageManager.getCurPhoto() = new Photo(fileName);
            if(oldimg)delete oldimg;
        }
        imageManager.showImage();
//        QImage *img = new QImage(fileName);
//        if(!img)return;
//        QLabel *imageLabel = new QLabel(this);
//        imageLabel->setAlignment(Qt::AlignCenter);
//        imageLabel->setPixmap(QPixmap::fromImage(*img));
//        ui->imageGround->setBackgroundRole(QPalette::Dark);
//        ui->imageGround->setWidgetResizable(true);
//        ui->imageGround->setAlignment(Qt::AlignCenter);
//        ui->imageGround->setWidget(imageLabel);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionnew_file_N_triggered()
{
    openImage();
    imageManager.showImage();
//    QString filename;
//    filename = QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
//    int imgID = imageManager.loadQImage(filename);
//    qDebug() << "imgID: "<< imgID;
//    ImageIDs.push_back(imgID);
//    QImage *img = imageManager.getQImage(imgID);

//    int imgWidth = img->width();qDebug()<<"imgWidth: "<<imgWidth;
//    int imgHeight = img->height();qDebug()<<"imgHeight: "<<imgHeight;
//    float imgRate = float(imgWidth)/float(imgHeight);qDebug()<<"imgRate: "<<imgRate;

//    QLabel *imageLabel = new QLabel(this);
//    imageLabel->setAlignment(Qt::AlignCenter);
//    imageLabel->setPixmap(QPixmap::fromImage(*img));
//    ui->imageGround->setBackgroundRole(QPalette::Dark);
//    ui->imageGround->setWidgetResizable(true);
//    ui->imageGround->setWidget(imageLabel);
}

void MainWindow::on_actiontool_box_T_triggered()
{
    bool ischecked = ui->actiontool_box_T->isChecked();
    if(ischecked)ui->dockWidget->show();
    else ui->dockWidget->close();
}

void MainWindow::tool_box_T_2_dockWidget()
{
    if(ui->dockWidget->isHidden())
        ui->actiontool_box_T->setChecked(false);
    else ui->actiontool_box_T->setChecked(true);
}

void MainWindow::on_actionbaocun_S_triggered()
{
    saveImage();
}

void MainWindow::saveImage()
{
    if(imageManager.getCurPhoto() && imageManager.getCurPhoto()->IsEnabled()){
        QString savePath = QFileDialog::getSaveFileName(this,tr("保存文件"),"/",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
        imageManager.saveImage(savePath);
    }
}

void MainWindow::openImage()
{
    // && imageManager.getCurPhoto()->IsEdited()
    if(imageManager.getCurPhoto() && imageManager.getCurPhoto()->IsEnabled()){
        SaveDialog sdlg;
        sdlg.exec();
//        sdlg.show();
        qDebug()<<"sdlg.state == SaveDialog::NOT_SAVE" << (sdlg.state == SaveDialog::NOT_SAVE);
    }
    else{
        QString filename = QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
        Photo * oldimg = imageManager.getCurPhoto();
        imageManager.getCurPhoto() = new Photo(filename);
        if(oldimg)delete oldimg;
    }
}




