#include "mainwindow.h"
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
#include <QTextStream>
#include <QDropEvent>
#include <QFileDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ImageManager()
{
    ImageIDs.clear();
    ui->setupUi(this);
    ui->statusBar->showMessage(tr("欢迎使用图之美"),2000);
    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText(tr("Image Beautify"));
    ui->statusBar->addPermanentWidget(permanent);

    connect(ui->dockWidget,SIGNAL(visibilityChanged(bool)),this,SLOT(tool_box_T_2_dockWidget()));
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

//void MainWindow::dragEnterEvent(QDragEnterEvent *event)
//{
//    if(event->mimeData()->hasImage())
//        event->acceptProposedAction();
//    else event->ignore();
//}

//void MainWindow::dropEvent(QDropEvent *event)
//{
//    const QMimeData * mimeData = event->mimeData();
//}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionnew_file_N_triggered()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    int imgID = ImageManager.loadQImage(filename);
    ImageIDs.push_back(imgID);

    QImage *img = ImageManager.getQImage(imgID);
//    QImage img(filename);


//    qDebug()<<"filename is: "<<filename;
//    qDebug()<<"filename index of '/' is: "<<filename.indexOf('/');

    int imgWidth = img->width();qDebug()<<"imgWidth: "<<imgWidth;
    int imgHeight = img->height();qDebug()<<"imgHeight: "<<imgHeight;
    float imgRate = float(imgWidth)/float(imgHeight);qDebug()<<"imgRate: "<<imgRate;
    int mdiWidth = ui->mdiArea->width();qDebug()<<"mdiWidth: "<<mdiWidth;
    int mdiHeight = ui->mdiArea->height();qDebug()<<"mdiHeight: "<<imgHeight;
    if(imgRate > 1.0f)
        img->scaled(mdiWidth,int(mdiWidth*imgRate));
    else img->scaled(int(mdiHeight/imgRate),mdiHeight);
    qDebug()<<"imgWidth: "<<img->width();
    qDebug()<<"imgHeight: "<<img->height();

    QLabel *label = new QLabel(this);
    label->resize(img->height(),img->width());
    label->setAlignment(Qt::AlignCenter);
    label->setPixmap(QPixmap::fromImage(*img));
//    label->setPixmap(QPixmap("images/image.png"));
    QMdiSubWindow *child = ui->mdiArea->addSubWindow(label);
    ImageManager.bindView(imgID,child);

    int childWidth = child->width();qDebug()<<"childWidth: "<<childWidth;
    int childHeight = child->height();qDebug()<<"childHeight: "<<childHeight;

    child->setWindowTitle(filename);

    child->show();
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
    int allcnt = 0;
    int cnt = 0;
    int focusedChild = -1;
    for(int imgID:ImageIDs){
        allcnt++;
        QMdiSubWindow* view = ImageManager.getView(imgID);
        if(view && view->hasFocus()){
            cnt++;
            focusedChild = imgID;
            qDebug()<<"has focus: "<<view->windowTitle();
        }
    }
    qDebug()<<"allcnt: "<<allcnt;
    qDebug()<<"cnt: "<<cnt;
    qDebug()<<"focusedChild: "<<focusedChild;
    if(focusedChild != -1){
        QString savePath = QFileDialog::getSaveFileName(this,tr("保存文件"),"/",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
        qDebug()<<"savePath: "<<savePath;
        ImageManager.getQImage(focusedChild)->save(savePath);
    }
}
