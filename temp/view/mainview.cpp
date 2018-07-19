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
#include <QClipboard>
#include <QMimeData>
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
    initializeEditMenu();
    initializeToolsMenu();
    initializeSpecialEffectsMenu();
    initializeFrameMenu();
    initializeViewMenu();
    initializeAboutMenu();
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

    QAction *exitAct = fileMenu->addAction(tr("exit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));
}

void MainView::open(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString initPath = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();
    QString filePath = QFileDialog::getOpenFileName(this,tr("Save File As"),initPath,tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filePath == "")return;

    openFileCommand->SetParameter(std::make_shared<StringParameters>(filePath.toStdString()));
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

    saveFileCommand->SetParameter(std::make_shared<StringParameters>(savePath.toStdString()));
    saveFileCommand->Exec();

    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(savePath));
    statusBar()->showMessage(message);
}

/******************* edit menu ********************/
void MainView::initializeEditMenu(){
    QMenu *editMenu = menuBar()->addMenu(tr("编辑"));

    undoAct = editMenu->addAction(tr("撤销"), this, &MainView::undo);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setEnabled(false);

    redoAct = editMenu->addAction(tr("重做"), this, &MainView::redo);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setEnabled(false);

    editMenu->addSeparator();

    copyAct = editMenu->addAction(tr("复制"), this, &MainView::copy);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(false);

    QAction *pasteAct = editMenu->addAction(tr("粘贴"), this, &MainView::paste);
    pasteAct->setShortcut(QKeySequence::Paste);
}

void MainView::undo(){}
void MainView::redo(){}

void MainView::copy(){
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(*image);
#endif // !QT_NO_CLIPBOARD
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage()
{
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
        if (mimeData->hasImage()) {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull())
                return image;
        }
    }
    return QImage();
}
#endif // !QT_NO_CLIPBOARD

void MainView::paste(){
//#ifndef QT_NO_CLIPBOARD
//    const QImage newImage = clipboardImage();
//    if (newImage.isNull()) {
//        statusBar()->showMessage(tr("No image in clipboard"));
//    } else {
//        setImage(newImage);
//        setWindowFilePath(QString());
//        const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
//            .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
//        statusBar()->showMessage(message);
//    }
//#endif // !QT_NO_CLIPBOARD
}

/******************* tools menu ********************/
void MainView::initializeToolsMenu(){
    toolsMenu = menuBar()->addMenu(tr("工具"));
    toolsMenu->setEnabled(false);

    QMenu *channelSubMenu = toolsMenu->addMenu(tr("&Channel Separation"));
    channelSubMenu->addAction(tr("&Red Channel"), this, SLOT(redChannel()));
    channelSubMenu->addAction(tr("&Green Channel"), this, SLOT(greenChannel()));
    channelSubMenu->addAction(tr("&Blue Channel"), this, SLOT(blueChannel()));

    toolsMenu->addAction(tr("&Gray-Scale Transfer"), this, SLOT(grayScaleTransfer()));

    QMenu *adjustSubMenu = toolsMenu->addMenu(tr("&Adjust Image"));
    adjustSubMenu->addAction(tr("&Hue/Saturation/Lightness..."), this, SLOT(hueSaturationLightness()));
    adjustSubMenu->addAction(tr("&Contrast Curve..."), this, SLOT(curve()));
    adjustSubMenu->addAction(tr("&Level..."), this, SLOT(level()));
    adjustSubMenu->addAction(tr("&Clip..."), this, SLOT(clip()));
    adjustSubMenu->addAction(tr("&Scale/Rotation..."), this, SLOT(scale()));

    toolsMenu->addAction(tr("&Histogram..."), this, SLOT(histogram()));

    toolsMenu->addSeparator();

    QMenu *imageBinarizationSubMenu = toolsMenu->addMenu(tr("&Image Binarization"));
    imageBinarizationSubMenu->addAction(tr("&OTSU"), this, SLOT(otsu()));
    imageBinarizationSubMenu->addAction(tr("Dual Threshold"), this, SLOT(dualThreshold()));

    toolsMenu->addAction(tr("&Algebraic Operations..."), this, SLOT(algebraic));
    toolsMenu->addAction(tr("&Filtering..."), this, SLOT(filter()));
    toolsMenu->addAction(tr("&Edge Detection..."), this, SLOT(edgeDetection()));

    QMenu *houghTransformSubMenu = toolsMenu->addMenu(tr("&Hough Transform"));
    houghTransformSubMenu->addAction(tr("Detect &Line"), this, SLOT(houghLineDetect()));
    houghTransformSubMenu->addAction(tr("Detect &Circle..."), this, SLOT(houghCircleDetect()));

    QMenu *mathematicalMorphologySubMenu = toolsMenu->addMenu(tr("&Mathematical Morphology"));
    mathematicalMorphologySubMenu->addAction(tr("&Binary Morphology..."), this, SLOT(binaryMorphology()));
    mathematicalMorphologySubMenu->addAction(tr("Gray-scale Morphology..."), this, SLOT(grayMorphology()));
}

void MainView::redChannel(){}
void MainView::greenChannel(){}
void MainView::blueChannel(){}
void MainView::grayScaleTransfer(){}
void MainView::hueSaturationLightness(){}
void MainView::curve(){}
void MainView::level(){}
void MainView::clip(){}
void MainView::scale(){}
void MainView::histogram(){}
void MainView::otsu(){}
void MainView::dualThreshold(){}
void MainView::algebraic(){}
void MainView::filter(){}
void MainView::edgeDetection(){}
void MainView::houghLineDetect(){}
void MainView::houghCircleDetect(){}
void MainView::binaryMorphology(){}
void MainView::grayMorphology(){}

/******************* special effects menu ********************/
void MainView::initializeSpecialEffectsMenu(){
    specialEffectsMenu = menuBar()->addMenu(tr("特效"));
    specialEffectsMenu->setEnabled(false);

    specialEffectsMenu->addAction(tr("热门特效..."),this,SLOT(hotSpecialEffects()));
    specialEffectsMenu->addAction(tr("基础特效..."),this,SLOT(basicSpecialEffects()));
    specialEffectsMenu->addAction(tr("LOMO特效..."),this,SLOT(lomoSpecialEffects()));
    specialEffectsMenu->addAction(tr("人像特效..."),this,SLOT(humanFaceSpecialEffects()));
    specialEffectsMenu->addAction(tr("时尚特效..."),this,SLOT(fashionSpecialEffects()));
    specialEffectsMenu->addAction(tr("艺术特效..."),this,SLOT(artSpecialEffects()));
}

void MainView::hotSpecialEffects(){}
void MainView::basicSpecialEffects(){}
void MainView::lomoSpecialEffects(){}
void MainView::humanFaceSpecialEffects(){}
void MainView::fashionSpecialEffects(){}
void MainView::artSpecialEffects(){}

/******************* frame menu ********************/
void MainView::initializeFrameMenu(){
    frameMenu = menuBar()->addMenu(tr("边框"));
    frameMenu->setEnabled(false);

    frameMenu->addAction(tr("炫彩边框..."),this,SLOT(colorfulFrame()));
    frameMenu->addAction(tr("简单边框..."),this,SLOT(simpleFrame()));
    frameMenu->addAction(tr("纹理边框..."),this,SLOT(textureFrame()));
    frameMenu->addAction(tr("撕边边框..."),this,SLOT(tearFrame()));
    frameMenu->addAction(tr("轻松边框..."),this,SLOT(relaxedFrame()));
}

void MainView::colorfulFrame(){}
void MainView::simpleFrame(){}
void MainView::textureFrame(){}
void MainView::tearFrame(){}
void MainView::relaxedFrame(){}

/******************* view menu ********************/
void MainView::initializeViewMenu(){
    QMenu *viewMenu = menuBar()->addMenu(tr("视图"));

    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &MainView::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &MainView::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &MainView::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+I"));
    normalSizeAct->setEnabled(false);

    viewMenu->addSeparator();

    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &MainView::fitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
}

void MainView::zoomIn()
{
    scaleImage(1.25);
}

void MainView::zoomOut()
{
    scaleImage(0.8);
}

void MainView::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void MainView::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSize();
    updateActions();
}

void MainView::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void MainView::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

/******************* about menu ********************/
void MainView::initializeAboutMenu(){
    QMenu *helpMenu = menuBar()->addMenu(tr("帮助"));

    helpMenu->addAction(tr("关于"), this, &MainView::about);
}

void MainView::about(){
    QMessageBox::about(this, tr("About ImageBeautify"),
                tr("<p><strong>版本:1.x版</strong></p>"
                   "<p><strong>日期:</strong> 2018-07-11T15:43:53.668Z</p>"
                   "<p><strong>架构:</strong> x86/x64/</p>"
                   "<p><strong>框架:</strong> MVVM</p>"
                   "<p><strong>作者:</strong> kk,  cc,  ye.</p>"
                   "<p><strong>版权声明:</strong>本作品采用知识共享署名-非商业性使用-禁止演绎 3.0 中 国大陆许可协议进行许可。要查看该许可协议，可访问 <a href='http://creativecommons.org/licenses/by-nc-nd/3.0/cn/' target='_blank' class='url'>http://creativecommons.org/licenses/by-nc-nd/3.0/cn/</a> 或者写 信到 Creative Commons, PO Box 1866, Mountain View, CA 94042, USA。</p>"
                   "<p>&nbsp;</p>"));
}


/**************************************************/
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

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

void MainView::updateActions(){
    fitToWindowAct->setEnabled(true);

    toolsMenu->setEnabled(!image->isNull());
    specialEffectsMenu->setEnabled(!image->isNull());
    frameMenu->setEnabled(!image->isNull());

    saveAsAct->setEnabled(!image->isNull());
    copyAct->setEnabled(!image->isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

