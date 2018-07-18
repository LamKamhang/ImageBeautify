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
#include <QscrollBar>
#include "mainview.h"

MainView::MainView()
    : imageLabel(new QLabel)
    , positionLabel(new QLabel)
    , pixelColorLabel(new QLabel)
    , pixelRGBLabel(new QLabel)
    , scrollArea(new QScrollArea)
    , scaleFactor(1)
{
    mainViewSink = std::make_shared<MainImageSink>(MainImageSink(this));

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
//    initializeEditMenu();
//    initializeToolsMenu();
//    initializeSpecialEffectsMenu();
//    initializeFrameMenu();
//    initializeViewMenu();
//    initializeAboutMenu();
}

/******************* file menu ********************/
void MainView::initializeFileMenu(){
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));

    QAction *openAct = fileMenu->addAction(tr("打开..."), this, &MainView::open);
    openAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("另存为..."), this, &MainView::saveAs);
    saveAsAct->setShortcut(tr("Ctrl+S"));
    saveAsAct->setEnabled(false);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("退出"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));
}

void MainView::open(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString initPath = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();
    QString filePath = QFileDialog::getOpenFileName(this,tr("Save File As"),initPath,tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filePath == "")return;

    openFileCommand->SetParameter(std::static_pointer_cast<Parameters, PathParameters>(std::shared_ptr<PathParameters>(new PathParameters(filePath.toStdString()))));
    openFileCommand->Exec();

    setWindowFilePath(filePath);
    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(filePath)).arg(image->width()).arg(image->height()).arg(image->depth());
    statusBar()->showMessage(message);
}

void MainView::saveAs(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString initPath = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();
    QString savePath = QFileDialog::getSaveFileName(this,tr("Save File As"),initPath,tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(savePath == "")return;

    saveFileCommand->SetParameter(std::static_pointer_cast<Parameters, PathParameters>(std::shared_ptr<PathParameters>(new PathParameters(savePath.toStdString()))));
    saveFileCommand->Exec();

    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(savePath));
    statusBar()->showMessage(message);
}



void MainView::setImage(std::shared_ptr<QImage> img){
    image = img;
}

void MainView::setOpenFileCommand(std::shared_ptr<ICommandBase> command){
    openFileCommand = command;
}

void MainView::setSaveFileCommand(std::shared_ptr<ICommandBase> command){
    saveFileCommand = command;
}

std::shared_ptr<IPropertyNotification> MainView::getMainViewSink(){
    return std::static_pointer_cast<IPropertyNotification>(mainViewSink);
}

