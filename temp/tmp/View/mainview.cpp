#include "mainview.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QstatusBar>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QScreen>
#include <QStandardPaths>

#include "Commands/open_file_command.h"
#include "Commands/save_file_command.h"
#include "Notification/notification.h"

MainView::MainView()
    : imageLabel(new QLabel)
    , positionLabel(new QLabel)
    , pixelColorLabel(new QLabel)
    , pixelRGBLabel(new QLabel)
    , scrollArea(new QScrollArea)
    , scaleFactor(1)
{
    update_mainview_notification = std::static_pointer_cast<Notification, UpdateMainViewNotification>(std::shared_ptr<UpdateMainViewNotification>(new UpdateMainViewNotification(std::shared_ptr<MainView>(this))));

    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setAlignment(Qt::AlignCenter);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setVisible(false);
    setCentralWidget(scrollArea);

    positionLabel->setText(tr(""));

    statusBar()->addPermanentWidget(pixelColorLabel);
    statusBar()->addPermanentWidget(pixelRGBLabel);
    statusBar()->addPermanentWidget(positionLabel);

    this->setMouseTracking(true);
    scrollArea->setMouseTracking(true);
    imageLabel->setMouseTracking(true);

    initializeViews();

    resize(QGuiApplication::primaryScreen()->availableSize() * 0.8);
}

MainView::~MainView(){
    delete ui;
}

void MainView::initializeViews(){
    initializeFileMenu();
}

void MainView::initializeFileMenu(){
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));

    QAction *openAct = fileMenu->addAction(tr("打开..."), this, &MainView::open);
    openAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("另存为..."), this, &MainView::saveAs);
    saveAsAct->setShortcut(tr("Ctrl+S"));
    saveAsAct->setEnabled(false);
}

void MainView::set_open_file_command(std::shared_ptr<Command> command){
    open_file_command = command;
}

void MainView::set_save_file_command(std::shared_ptr<Command> command){
    save_file_command = command;
}

void MainView::set_img(std::shared_ptr<QImage> img){
    image = img;
}

std::shared_ptr<Notification> MainView::get_update_mainview_notification(){
    return update_mainview_notification;
}

void MainView::mouseMoveEvent(QMouseEvent *e){
    QString posMsg;
    QString rgbMsg;
    int x = e->x();
    int y = e->y();
    QRect imageRect = QRect(imageLabel->pos() + scrollArea->pos(), imageLabel->size());
    if(image->isNull()
            || !imageRect.contains(e->pos())){
        posMsg = "  Windows position: ";
        posMsg += "(" + QString::number(x) + "," + QString::number(y) + ")";
        rgbMsg = " RGB(#,#,#)";
        pixelColorLabel->clear();
    }
    else {
        QSize initSize = imageLabel->pixmap()->size();
        posMsg = "  Canvas position: ";
        int imageX = (x - imageRect.x()) * initSize.width() / imageRect.width();
        int imageY = (y - imageRect.y()) * initSize.height() / imageRect.height();
        posMsg += "(" + QString::number(imageX) + "," + QString::number(imageY) + ")";

        QRgb rgb = image->pixel(imageX, imageY);
        rgbMsg = " RGB(" + QString::number(qRed(rgb)) + ","
                + QString::number(qGreen(rgb)) + ","
                + QString::number(qBlue(rgb)) + ")";
        QPixmap pixelColor(20, 20);
        pixelColor.fill(QColor(rgb));
        pixelColorLabel->setPixmap(pixelColor);
    }
    positionLabel->setText(posMsg);
    pixelRGBLabel->setText(rgbMsg);
}

void MainView::update(){
    imageLabel->setPixmap(QPixmap::fromImage(*image));
    scaleFactor = 1.0;
    scrollArea->setVisible(true);

//    set actions enable
    updateActions();

//    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

void MainView::open(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString initPath = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();
    QString filePath = QFileDialog::getOpenFileName(this,tr("Save File As"),initPath,tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filePath == "")return;
    open_file_command->set_parameters(std::static_pointer_cast<Parameters, PathParameters>(std::shared_ptr<PathParameters>(new PathParameters(filePath.toStdString()))));
    open_file_command->exec();
}

void MainView::saveAs(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString initPath = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();
    QString savePath = QFileDialog::getSaveFileName(this,tr("Save File As"),initPath,tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(savePath == "")return;
    save_file_command->set_parameters(std::static_pointer_cast<Parameters, PathParameters>(std::shared_ptr<PathParameters>(new PathParameters(savePath.toStdString()))));
    save_file_command->exec();
}

void MainView::updateActions(){
    saveAsAct->setEnabled(!image->isNull());
}
