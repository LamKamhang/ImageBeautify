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
#include <QString>
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

    QAction *exitAct = fileMenu->addAction(tr("退出"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));
}

void MainView::open(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString initPath = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();
    QString filePath = QFileDialog::getOpenFileName(this,tr("Save File As"),initPath,tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filePath == "")return;

    openFileCommand->SetParameter(std::make_shared<QStringParameters>(filePath));
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

    saveFileCommand->SetParameter(std::make_shared<QStringParameters>(savePath));
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

void MainView::undo(){
    undoCommand->Exec();
}
void MainView::redo(){
    redoCommand->Exec();
}

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
    imageBinarizationSubMenu->addAction(tr("Dual Threshold..."), this, SLOT(dualThreshold()));

    toolsMenu->addAction(tr("&Algebraic Operations..."), this, SLOT(algebraic()));
    toolsMenu->addAction(tr("&Filtering..."), this, SLOT(filter()));
    toolsMenu->addAction(tr("&Edge Detection..."), this, SLOT(edgeDetection()));

    QMenu *houghTransformSubMenu = toolsMenu->addMenu(tr("&Hough Transform"));
    houghTransformSubMenu->addAction(tr("Detect &Line"), this, SLOT(houghLineDetect()));
    houghTransformSubMenu->addAction(tr("Detect &Circle..."), this, SLOT(houghCircleDetect()));

    QMenu *mathematicalMorphologySubMenu = toolsMenu->addMenu(tr("&Mathematical Morphology"));
    mathematicalMorphologySubMenu->addAction(tr("&Binary Morphology..."), this, SLOT(binaryMorphology()));
    mathematicalMorphologySubMenu->addAction(tr("Gray-scale Morphology..."), this, SLOT(grayMorphology()));
}

void MainView::redChannel(){
    channelCommand->SetParameter(std::make_shared<EnumCommandParameters>(RED_CHANNEL));
    channelCommand->Exec();
}
void MainView::greenChannel(){
    channelCommand->SetParameter(std::make_shared<EnumCommandParameters>(GREEN_CHANNEL));
    channelCommand->Exec();
}
void MainView::blueChannel(){
    channelCommand->SetParameter(std::make_shared<EnumCommandParameters>(BLUE_CHANNEL));
    channelCommand->Exec();
}
void MainView::grayScaleTransfer(){
    grayScaleTransferCommand->Exec();
}

void MainView::hueSaturationLightness(){
    openSubDialogCommand->Exec();// set mainimg to subimg
    HueSaturaLightDialog *dialog = new HueSaturaLightDialog(this,subimage);
    connect(dialog, SIGNAL(sendApplyHSLAdjust(std::shared_ptr<JsonParameters>))
            , this, SLOT(receiveApplyHueSaturaLight(std::shared_ptr<JsonParameters>)));
    connect(this, SIGNAL(subImageChanged()), dialog,SLOT(update()));
    dialog->exec();
}

void MainView::receiveApplyHueSaturaLight(std::shared_ptr<JsonParameters> json){
    hueSaturaLightCommand->SetParameter(json);
    hueSaturaLightCommand->Exec();
}

void MainView::curve(){
    openSubDialogCommand->Exec();// set mainimg to subimg
    CurveDialog *dialog = new CurveDialog(subimage);
    connect(dialog,SIGNAL(sendApplyCurve(std::shared_ptr<JsonParameters>))
            , this,SLOT(receiveApplyCurve(std::shared_ptr<JsonParameters>)));
    connect(this,SIGNAL(subImageChanged()),dialog,SLOT(update()));
    dialog->exec();
}

void MainView::level(){
    openSubDialogCommand->Exec();// set mainimg to subimg
    LevelDialog *dialog = new LevelDialog(subimage);
    connect(dialog,SIGNAL(sendApplyLevelAdjust(std::shared_ptr<JsonParameters>))
            , this,SLOT(receiveApplyLevel(std::shared_ptr<JsonParameters>)));
    connect(this,SIGNAL(subImageChanged()),dialog,SLOT(update()));
    dialog->exec();
}

void MainView::clip(){
    ClipDialog *dialog = new ClipDialog(QPixmap::fromImage(*image));
    connect(dialog,SIGNAL(sendApplyClip(std::shared_ptr<JsonParameters>))
            , this,SLOT(receiveApplyClip(std::shared_ptr<JsonParameters>)));
    dialog->exec();
}

void MainView::scale(){
   ScaleDialog *dialog = new ScaleDialog();
   connect(dialog,SIGNAL(sendApplyScale(std::shared_ptr<JsonParameters>))
           , this,SLOT(receiveApplyScale(std::shared_ptr<JsonParameters>)));
   dialog->exec();
}

void MainView::histogram(){
   HistogramDialog *dialog = new HistogramDialog(image);
   connect(dialog,SIGNAL(sendApplyHistogramEqualization(std::shared_ptr<VectorParameters<int> >))
           , this,SLOT(receiveApplyHistogram(std::shared_ptr<VectorParameters<int> >)));
   dialog->exec();
}

void MainView::otsu(){
    otsuCommand->Exec();
}

void MainView::dualThreshold(){
    openSubDialogCommand->Exec();// set mainimg to subimg
    DualThresholdDialog *dialog = new DualThresholdDialog(this,subimage);
    connect(dialog, SIGNAL(sendApplyDualThreshold(std::shared_ptr<JsonParameters>))
            ,this, SLOT(receiveApplyDualThreshold(std::shared_ptr<JsonParameters>)));
    connect(this, SIGNAL(subImageChanged()), dialog, SLOT(update()));
    dialog->exec();
}

void MainView::receiveApplyDualThreshold(std::shared_ptr<JsonParameters> json){
    dualThresholdCommand->SetParameter(json);
    dualThresholdCommand->Exec();
}

void MainView::receiveApplyCurve(std::shared_ptr<JsonParameters> json){
    curveCommand->SetParameter(json);
    curveCommand->Exec();
}

void MainView::receiveApplyLevel(std::shared_ptr<JsonParameters> json){
    levelCommand->SetParameter(json);
    levelCommand->Exec();
}

void MainView::receiveApplyClip(std::shared_ptr<JsonParameters> json){
    clipCommand->SetParameter(json);
    clipCommand->Exec();
}

void MainView::receiveApplyScale(std::shared_ptr<JsonParameters> json){
    scaleCommand->SetParameter(json);
    scaleCommand->Exec();
}

void MainView::receiveApplyHistogram(std::shared_ptr<VectorParameters<int> > histo){
    histogramCommand->SetParameter(histo);
    histogramCommand->Exec();
}

void MainView::receiveApplyAlgebraic(std::shared_ptr<JsonParameters> json){
    algebraicCommand->SetParameter(json);
    algebraicCommand->Exec();
}

void MainView::receiveAlgebraicOpenFileImage2(QString filePath){
    openSubFileCommand->SetParameter(std::make_shared<QStringParameters>(filePath));
    openSubFileCommand->Exec();
}

void MainView::algebraic(){
    AlgebraicDialog *dialog = new AlgebraicDialog(this,*image,subimage);
    connect(dialog,SIGNAL(sendApplyAlgebraicOperation(std::shared_ptr<JsonParameters>))
            , this, SLOT(receiveApplyAlgebraic(std::shared_ptr<JsonParameters>)));
    connect(dialog,SIGNAL(sendOpenFileImage2(QString))
            ,this, SLOT(receiveAlgebraicOpenFileImage2(QString)));
    connect(this,SIGNAL(subImageChanged()),dialog,SLOT(updateImage2()));
    dialog->exec();
}

void MainView::filter(){
    FilterDialog *dialog = new FilterDialog();
    connect(dialog,SIGNAL(sendApplyFilter(std::shared_ptr<JsonParameters>))
            ,this,SLOT(receiveApplyFilter(std::shared_ptr<JsonParameters>)));
    dialog->exec();
}

void MainView::receiveApplyFilter(std::shared_ptr<JsonParameters> json){
    setCursor(Qt::WaitCursor);
    filterCommand->SetParameter(json);
    filterCommand->Exec();
}

void MainView::edgeDetection(){
    EdgeDetectionDialog *dialog = new EdgeDetectionDialog();
    connect(dialog,SIGNAL(sendApplyEdgeDetection(std::shared_ptr<JsonParameters>))
            ,this,SLOT(receiveApplyEdgeDetection(std::shared_ptr<JsonParameters>)));
    dialog->exec();
}

void MainView::receiveApplyEdgeDetection(std::shared_ptr<JsonParameters> json){
    setCursor(Qt::WaitCursor);
    edgeDetectionCommand->SetParameter(json);
    edgeDetectionCommand->Exec();
}

void MainView::houghLineDetect(){
    setCursor(Qt::WaitCursor);
    houghLineDetectionCommand->Exec();
}

void MainView::houghCircleDetect(){
    HoughCircleDetectionDialog *dialog = new HoughCircleDetectionDialog();
    connect(dialog, SIGNAL(sendApplyHoughCircleDetection(std::shared_ptr<JsonParameters>))
            , this, SLOT(receiveApplyHoughCircleDetection(std::shared_ptr<JsonParameters>)));
    dialog->exec();
}

void MainView::receiveApplyHoughCircleDetection(std::shared_ptr<JsonParameters> json){
    setCursor(Qt::WaitCursor);
    houghCircleDetectionCommand->SetParameter(json);
    houghCircleDetectionCommand->Exec();
}

void MainView::binaryMorphology(){

}

void MainView::grayMorphology(){

}

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
                tr("<p><b>Image Beautify</b> is based on MVVM framework and Qt/C++,"
                   " and the core algrithms are implemented with OpenCV."));
}


/**************************************************/
void MainView::setImage(std::shared_ptr<QImage> img){
    image = img;
}

void MainView::setSubImage(std::shared_ptr<QImage> img){
    subimage = img;
}

void MainView::setUndoEnabled(std::shared_ptr<bool> u){
    undoEnabled = u;
}

void MainView::setRedoEnabled(std::shared_ptr<bool> r){
    redoEnabled = r;
}

void MainView::setUndoMsg(std::shared_ptr<QString> u){
    undoMsg = u;
}

void MainView::setRedoMsg(std::shared_ptr<QString> r){
    redoMsg = r;
}

void MainView::setIsBinary(std::shared_ptr<bool> binary){
    isBinary = binary;
}

void MainView::setIsGray(std::shared_ptr<bool> gray){
    isGray = gray;
}

void MainView::setOpenFileCommand(std::shared_ptr<ICommandBase> command){
    openFileCommand = command;
}

void MainView::setSaveFileCommand(std::shared_ptr<ICommandBase> command){
    saveFileCommand = command;
}

void MainView::setBinaryMorphologyCommand(std::shared_ptr<ICommandBase> command){
    binaryMorphologyCommand = command;
}

void MainView::setOpenSubDialogCommand(std::shared_ptr<ICommandBase> command){
    openSubDialogCommand = command;
}

void MainView::setOpenSubFileCommand(std::shared_ptr<ICommandBase> command){
    openSubFileCommand = command;
}

void MainView::setUndoCommand(std::shared_ptr<ICommandBase> command){
    undoCommand = command;
}

void MainView::setRedoCommand(std::shared_ptr<ICommandBase> command){
    redoCommand = command;
}

void MainView::setFilterCommand(std::shared_ptr<ICommandBase> command){
    filterCommand = command;
}

void MainView::setEdgeDetectionCommand(std::shared_ptr<ICommandBase> command){
    edgeDetectionCommand = command;
}

void MainView::setHoughCircleDetectionCommand(std::shared_ptr<ICommandBase> command){
    houghCircleDetectionCommand = command;
}

void MainView::setChannelCommand(std::shared_ptr<ICommandBase> command){
    channelCommand = command;
}

void MainView::setGrayScaleTransferCommand(std::shared_ptr<ICommandBase> command){
    grayScaleTransferCommand = command;
}

void MainView::setOtsuCommand(std::shared_ptr<ICommandBase> command){
    otsuCommand = command;
}

void MainView::setHoughLineDetectionCommand(std::shared_ptr<ICommandBase> command){
    houghLineDetectionCommand = command;
}

void MainView::setDualThresholdCommand(std::shared_ptr<ICommandBase> command){
    dualThresholdCommand = command;
}

void MainView::setHueSaturaLightCommand(std::shared_ptr<ICommandBase> command){
    hueSaturaLightCommand = command;
}

void MainView::setCurveCommand(std::shared_ptr<ICommandBase> command){
    curveCommand = command;
}

void MainView::setLevelCommand(std::shared_ptr<ICommandBase> command){
    levelCommand = command;
}

void MainView::setClipCommand(std::shared_ptr<ICommandBase> command){
    clipCommand = command;
}

void MainView::setScaleCommand(std::shared_ptr<ICommandBase> command){
    scaleCommand = command;
}

void MainView::setHistogramCommand(std::shared_ptr<ICommandBase> command){
    histogramCommand = command;
}

void MainView::setAlgebraicCommand(std::shared_ptr<ICommandBase> command){
    algebraicCommand = command;
}

std::shared_ptr<IPropertyNotification> MainView::getMainViewSink(){
    return std::static_pointer_cast<IPropertyNotification>(mainViewSink);
}

std::shared_ptr<ICommandNotification> MainView::getMainCommandSink(){
    return std::static_pointer_cast<ICommandNotification>(mainCommandSink);
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

    setCursor(Qt::ArrowCursor);
}

void MainView::updateSubImage(){
    emit subImageChanged();
}

void MainView::updateLogManager(){
    undoAct->setEnabled(*undoEnabled);
    if(*undoEnabled){
        undoAct->setStatusTip("Undo: " + *undoMsg);
    } else {
        undoAct->setStatusTip(tr(""));
    }
    redoAct->setEnabled(*redoEnabled);
    if(*redoEnabled){
        redoAct->setStatusTip("Redo: " + *redoMsg);
    } else {
        redoAct->setStatusTip(tr(""));
    }
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

