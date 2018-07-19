#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#endif
#include <iostream>
#include "photoshopgui.h"

PhotoshopGUI::PhotoshopGUI()
    : imageLabel(new QLabel)
    , positionLabel(new QLabel)
    , pixelColorLabel(new QLabel)
    , pixelRGBLabel(new QLabel)
    , scrollArea(new QScrollArea)
    , scaleFactor(1)
    , log(new Log)
    , imageOperation(new ImageOperations)
{
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

void PhotoshopGUI::initializeViews(){
    initializeFileMenu();
    initializeEditMenu();
    initializeImageMenu();
    initializeSpecialEffectsMenu();
    initializeFrameMenu();
    initializeViewMenu();
    initializeAboutMenu();
}

void PhotoshopGUI::initializeFileMenu(){
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));

    QAction *openAct = fileMenu->addAction(tr("打开..."), this, &PhotoshopGUI::open);
    openAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("另存为..."), this, &PhotoshopGUI::saveAs);
    saveAsAct->setShortcut(tr("Ctrl+S"));
    saveAsAct->setEnabled(false);

    printAct = fileMenu->addAction(tr("打印..."), this, &PhotoshopGUI::print);
    printAct->setShortcut(QKeySequence::Print);
    printAct->setEnabled(false);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("退出"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));
}

void PhotoshopGUI::initializeEditMenu(){
    QMenu *editMenu = menuBar()->addMenu(tr("编辑"));

    undoAct = editMenu->addAction(tr("撤销"), this, &PhotoshopGUI::undo);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setEnabled(false);

    redoAct = editMenu->addAction(tr("重做"), this, &PhotoshopGUI::redo);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setEnabled(false);

    editMenu->addSeparator();

    copyAct = editMenu->addAction(tr("复制"), this, &PhotoshopGUI::copy);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(false);

    QAction *pasteAct = editMenu->addAction(tr("粘贴"), this, &PhotoshopGUI::paste);
    pasteAct->setShortcut(QKeySequence::Paste);
}

void PhotoshopGUI::initializeImageMenu(){
    imageMenu = menuBar()->addMenu(tr("工具"));
    imageMenu->setEnabled(false);

    QMenu *channelSubMenu = imageMenu->addMenu(tr("&Channel Separation"));
    channelSubMenu->addAction(tr("&Red Channel"), this, SLOT(redChannel()));
    channelSubMenu->addAction(tr("&Green Channel"), this, SLOT(greenChannel()));
    channelSubMenu->addAction(tr("&Blue Channel"), this, SLOT(blueChannel()));

    imageMenu->addAction(tr("&Gray-Scale Transfer"), this, SLOT(grayScaleTransfer()));

    QMenu *adjustSubMenu = imageMenu->addMenu(tr("&Adjust Image"));
    adjustSubMenu->addAction(tr("&Hue/Saturation/Lightness..."), this, SLOT(hueSaturationLightness()));
    adjustSubMenu->addAction(tr("&Contrast Curve..."), this, SLOT(curve()));
    adjustSubMenu->addAction(tr("&Level..."), this, SLOT(level()));
    adjustSubMenu->addAction(tr("&Clip..."), this, SLOT(clip()));
    adjustSubMenu->addAction(tr("&Scale/Rotation..."), this, SLOT(scale()));

    imageMenu->addAction(tr("&Histogram..."), this, SLOT(histogram()));

    imageMenu->addSeparator();

    QMenu *imageBinarizationSubMenu = imageMenu->addMenu(tr("&Image Binarization"));
    imageBinarizationSubMenu->addAction(tr("&OTSU"), this, SLOT(otsu()));
    imageBinarizationSubMenu->addAction(tr("Dual Threshold"), this, SLOT(dualThreshold()));

    imageMenu->addAction(tr("&Algebraic Operations..."), this, &PhotoshopGUI::algebraic);
    imageMenu->addAction(tr("&Filtering..."), this, SLOT(filter()));
    imageMenu->addAction(tr("&Edge Detection..."), this, SLOT(edgeDetection()));

    QMenu *houghTransformSubMenu = imageMenu->addMenu(tr("&Hough Transform"));
    houghTransformSubMenu->addAction(tr("Detect &Line"), this, SLOT(houghLineDetect()));
    houghTransformSubMenu->addAction(tr("Detect &Circle..."), this, SLOT(houghCircleDetect()));

    QMenu *mathematicalMorphologySubMenu = imageMenu->addMenu(tr("&Mathematical Morphology"));
    mathematicalMorphologySubMenu->addAction(tr("&Binary Morphology..."), this, SLOT(binaryMorphology()));
    mathematicalMorphologySubMenu->addAction(tr("Gray-scale Morphology..."), this, SLOT(grayMorphology()));
}

void PhotoshopGUI::initializeSpecialEffectsMenu(){
    specialEffectsMenu = menuBar()->addMenu(tr("特效"));
    specialEffectsMenu->setEnabled(false);

    specialEffectsMenu->addAction(tr("热门特效..."),this,SLOT(hotSpecialEffects()));
    specialEffectsMenu->addAction(tr("基础特效..."),this,SLOT(basicSpecialEffects()));
    specialEffectsMenu->addAction(tr("LOMO特效..."),this,SLOT(lomoSpecialEffects()));
    specialEffectsMenu->addAction(tr("人像特效..."),this,SLOT(humanFaceSpecialEffects()));
    specialEffectsMenu->addAction(tr("时尚特效..."),this,SLOT(fashionSpecialEffects()));
    specialEffectsMenu->addAction(tr("艺术特效..."),this,SLOT(artSpecialEffects()));
}

void PhotoshopGUI::hotSpecialEffects(){}
void PhotoshopGUI::basicSpecialEffects(){}
void PhotoshopGUI::lomoSpecialEffects(){}
void PhotoshopGUI::humanFaceSpecialEffects(){}
void PhotoshopGUI::fashionSpecialEffects(){}
void PhotoshopGUI::artSpecialEffects(){}

void PhotoshopGUI::receiveApplyHotSpecialEffects(){}
void PhotoshopGUI::receiveApplyBasicSpecialEffects(){}
void PhotoshopGUI::receiveApplyLomoSpecialEffects(){}
void PhotoshopGUI::receiveApplyHumanFaceSpecialEffects(){}
void PhotoshopGUI::receiveApplyFashionSpecialEffects(){}
void PhotoshopGUI::receiveApplyArtSpecialEffects(){}

void PhotoshopGUI::initializeFrameMenu(){
    frameMenu = menuBar()->addMenu(tr("边框"));
    frameMenu->setEnabled(false);

    frameMenu->addAction(tr("炫彩边框..."),this,SLOT(colorfulFrame()));
    frameMenu->addAction(tr("简单边框..."),this,SLOT(simpleFrame()));
    frameMenu->addAction(tr("纹理边框..."),this,SLOT(textureFrame()));
    frameMenu->addAction(tr("撕边边框..."),this,SLOT(tearFrame()));
    frameMenu->addAction(tr("轻松边框..."),this,SLOT(relaxedFrame()));
}

void PhotoshopGUI::colorfulFrame(){}
void PhotoshopGUI::simpleFrame(){}
void PhotoshopGUI::textureFrame(){}
void PhotoshopGUI::tearFrame(){}
void PhotoshopGUI::relaxedFrame(){}

void PhotoshopGUI::receiveApplyColorfulFrame(){}
void PhotoshopGUI::receiveApplySimpleFrame(){}
void PhotoshopGUI::receiveApplyTextureFrame(){}
void PhotoshopGUI::receiveApplyTearFrame(){}
void PhotoshopGUI::receiveApplyRelaxedFrame(){}

void PhotoshopGUI::initializeViewMenu(){
    QMenu *viewMenu = menuBar()->addMenu(tr("视图"));

    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &PhotoshopGUI::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &PhotoshopGUI::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &PhotoshopGUI::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+I"));
    normalSizeAct->setEnabled(false);

    viewMenu->addSeparator();

    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &PhotoshopGUI::fitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
}

void PhotoshopGUI::initializeAboutMenu(){
    QMenu *helpMenu = menuBar()->addMenu(tr("帮助"));

    helpMenu->addAction(tr("关于"), this, &PhotoshopGUI::about);
}

void PhotoshopGUI::mouseMoveEvent(QMouseEvent *e){
    QString posMsg;
    QString rgbMsg;
    int x = e->x();
    int y = e->y();
    QRect imageRect = QRect(imageLabel->pos() + scrollArea->pos(), imageLabel->size());
    if(image.isNull()
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

        QRgb rgb = image.pixel(imageX, imageY);
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

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void PhotoshopGUI::open(){
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

bool PhotoshopGUI::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    clearLog();

    setImage(newImage);

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;
}

void PhotoshopGUI::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    scrollArea->setVisible(true);
    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

void PhotoshopGUI::updateImage(const QImage &newImage){
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    if(!fitToWindowAct->isChecked())imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
}

bool PhotoshopGUI::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}

void PhotoshopGUI::saveAs()
{
//    QFileDialog dialog(this, tr("Save File As"));
//    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);
//    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString initPath = picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last();
    QString savePath = QFileDialog::getSaveFileName(this,tr("Save File As"),initPath,tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(savePath == "")return;
    saveFile(savePath);
}

void PhotoshopGUI::print()
{
    Q_ASSERT(imageLabel->pixmap());
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

void PhotoshopGUI::undo(){
    QImage img = log->undo(&image);
    updateImage(img);
    updateCommitManager();
}

void PhotoshopGUI::redo(){
    QImage img = log->redo();
    updateImage(img);
    updateCommitManager();
}

void PhotoshopGUI::copy()
{
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(image);
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

void PhotoshopGUI::paste()
{
#ifndef QT_NO_CLIPBOARD
    const QImage newImage = clipboardImage();
    if (newImage.isNull()) {
        statusBar()->showMessage(tr("No image in clipboard"));
    } else {
        setImage(newImage);
        setWindowFilePath(QString());
        const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
            .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
        statusBar()->showMessage(message);
    }
#endif // !QT_NO_CLIPBOARD
}

void PhotoshopGUI::redChannel(){
    makeCommit(image, "Channel Separation: Red");
    QImage newImage = imageOperation->getSingleChannel(image, ImageOperations::RED);
    updateImage(newImage);
}

void PhotoshopGUI::greenChannel(){
    makeCommit(image, "Channel Separation: Green");
    QImage newImage = imageOperation->getSingleChannel(image, ImageOperations::GREEN);
    updateImage(newImage);
}

void PhotoshopGUI::blueChannel(){
    makeCommit(image, "Channel Separation: Blue");
    QImage newImage = imageOperation->getSingleChannel(image, ImageOperations::BLUE);
    updateImage(newImage);
}

void PhotoshopGUI::grayScaleTransfer(){
    makeCommit(image, "Gray-Scale Transfer");
    QImage newImage = imageOperation->grayScale(image);
    updateImage(newImage);
}

void PhotoshopGUI::otsu(){
    makeCommit(image, "Image Binarization: OTSU");
    QImage newImage = imageOperation->otsu(image);
    updateImage(newImage);
}

void PhotoshopGUI::houghLineDetect(){
    setCursor(Qt::WaitCursor);
    makeCommit(image, "Hough Transform: Detect Line");
    QImage newImage = imageOperation->houghLineDetect(image);
    updateImage(newImage);
    setCursor(Qt::ArrowCursor);
}

void PhotoshopGUI::houghCircleDetect(){
    HoughTransformDialog *dialog = new HoughTransformDialog();
    connect(dialog, SIGNAL(sendApplyHoughTransform(QJsonObject)), this,
            SLOT(receiveApplyHoughTransform(QJsonObject)));
    dialog->exec();
}

void PhotoshopGUI::binaryMorphology(){
    bool isBinary = imageOperation->isBinaryImage(image);
    if(!isBinary){
        QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
                           tr("Current image is not binary image."));
        msgBox.exec();
        return;
    }
    BinaryMorphoDialog *dialog = new BinaryMorphoDialog();
    connect(dialog, SIGNAL(sendApplyBinaryMorpho(QJsonObject)), this,
            SLOT(receiveApplyBinaryMorpho(QJsonObject)));
    dialog->exec();
}

void PhotoshopGUI::grayMorphology(){
    bool isGray = imageOperation->isGrayImage(image);
    if(!isGray){
        QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
                           tr("Current image is not gray-scale image."));
        msgBox.exec();
        return;
    }
    GrayMorphoDialog *dialog = new GrayMorphoDialog();
    connect(dialog, SIGNAL(sendApplyGrayMorpho(QJsonObject)), this,
            SLOT(receiveApplyGrayMorpho(QJsonObject)));
    dialog->exec();
}

void PhotoshopGUI::clip(){
    ClipDialog *dialog = new ClipDialog(QPixmap::fromImage(image));
    connect(dialog, SIGNAL(sendApplyClip(QJsonObject)), this,
            SLOT(receiveApplyClip(QJsonObject)));
    dialog->exec();
}

void PhotoshopGUI::curve(){
    CurveDialog *dialog = new CurveDialog(image);
    connect(dialog, SIGNAL(sendApplyCurve(QJsonObject,QImage)), this,
            SLOT(receiveApplyCurve(QJsonObject,QImage)));
    dialog->exec();
}

void PhotoshopGUI::histogram(){
    HistogramDialog *dialog = new HistogramDialog(image);
    connect(dialog, SIGNAL(sendApplyHistogramEqualization(QImage)), this,
            SLOT(receiveApplyHistoEqualize(QImage)));
    dialog->exec();
}

void PhotoshopGUI::filter(){
    FilterDialog *dialog = new FilterDialog();
    connect(dialog, SIGNAL(sendApplyFilter(QJsonObject)), this,
            SLOT(receiveApplyFilter(QJsonObject)));
    dialog->exec();
}

void PhotoshopGUI::edgeDetection(){
    EdgeDetectionDialog *dialog = new EdgeDetectionDialog();
    connect(dialog, SIGNAL(sendApplyEdgeDetection(QJsonObject)), this,
            SLOT(receiveApplyEdgeDetection(QJsonObject)));
    dialog->exec();
}

void PhotoshopGUI::scale(){
    ScaleDialog *dialog = new ScaleDialog();
    connect(dialog, SIGNAL(sendApplyScale(QJsonObject)), this,
            SLOT(receiveApplyScale(QJsonObject)));
    dialog->exec();
}

void PhotoshopGUI::dualThreshold(){
    DualThresholdDialog *dialog = new DualThresholdDialog(this, image);
    connect(dialog, SIGNAL(sendApplyDualThreshold(QJsonObject,QImage)), this,
            SLOT(receiveApplyDualThreshold(QJsonObject,QImage)));
    dialog->exec();
}

void PhotoshopGUI::algebraic(){
    AlgebraicDialog *dialog = new AlgebraicDialog(this, image);
    connect(dialog, SIGNAL(sendApplyAlgebraicOperation(QJsonObject, QImage)), this,
            SLOT(receiveApplyAlgebraicOperation(QJsonObject,QImage)));
    dialog->exec();
}

void PhotoshopGUI::hueSaturationLightness(){
    HueSaturaLightDialog *dialog = new HueSaturaLightDialog(this, image);
    connect(dialog, SIGNAL(sendApplyHSLAdjust(QJsonObject,QImage)), this,
           SLOT(receiveApplyHSLAdjust(QJsonObject,QImage)));
    dialog->exec();
}

void PhotoshopGUI::level(){
    LevelDialog *dialog = new LevelDialog(image);
    connect(dialog, SIGNAL(sendApplyLevelAdjust(QImage)), this,
            SLOT(receiveApplyLevelAdjust(QImage)));
    dialog->exec();
}

void PhotoshopGUI::zoomIn()
{
//    makeCommit(image, "Zoom In");
    scaleImage(1.25);
}

void PhotoshopGUI::zoomOut()
{
//    makeCommit(image, "Zoom Out");
    scaleImage(0.8);
}

void PhotoshopGUI::normalSize()
{
//    makeCommit(image, "Normal Size");
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void PhotoshopGUI::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSize();
    updateActions();
}

void PhotoshopGUI::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void PhotoshopGUI::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void PhotoshopGUI::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<h3>Image Beautify</h3>"
               "<p><strong>版本：1.x版</strong></p>"
               "<p><strong>日期：</strong> 2018-07-11T15:43:53.668Z</p>"
               "<p><strong>架构：</strong> x86/x64/</p>"
               "<p><strong>作者：</strong> kk,  cc,  Ye.</p>"
               "<p><strong>版权声明：</strong>本作品采用知识共享署名-非商业性使用-禁止演绎 3.0 中 国大陆许可协议进行许可。要查看该许可协议，可访问 <a href='http://creativecommons.org/licenses/by-nc-nd/3.0/cn/' target='_blank' class='url'>http://creativecommons.org/licenses/by-nc-nd/3.0/cn/</a> 或者写 信到 Creative Commons, PO Box 1866, Mountain View, CA 94042, USA。</p>"
               "<p>&nbsp;</p>"));
}

void PhotoshopGUI::updateActions()
{
    imageMenu->setEnabled(!image.isNull());
    specialEffectsMenu->setEnabled(!image.isNull());
    frameMenu->setEnabled(!image.isNull());

    saveAsAct->setEnabled(!image.isNull());
    copyAct->setEnabled(!image.isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void PhotoshopGUI::makeCommit(QImage image, QString operation){
    log->commit(image, operation);
    updateCommitManager();
}

void PhotoshopGUI::clearLog(){
    log->clear();
    updateCommitManager();
}

void PhotoshopGUI::updateCommitManager(){
    bool undoEnabled = log->undoEnabled();
    bool redoEnabled = log->redoEnabled();
    undoAct->setEnabled(undoEnabled);
    if(undoEnabled){
        undoAct->setStatusTip("Undo: " + log->getUndoMsg());
    } else {
        undoAct->setStatusTip(tr(""));
    }
    redoAct->setEnabled(redoEnabled);
    if(redoEnabled){
        redoAct->setStatusTip("Redo: " + log->getRedoMsg());
    } else {
        redoAct->setStatusTip(tr(""));
    }
}

void PhotoshopGUI::receiveApplyAlgebraicOperation(QJsonObject json, QImage img){
    AlgebraicDialog::OperatorState op = (AlgebraicDialog::OperatorState)(json["operator"].toInt());
    QImage newImage;
    QString operationDesc;
    switch(op){
    case AlgebraicDialog::ADD:
        if(json["default"].toBool()){
            operationDesc = "image1 + image2";
            newImage = imageOperation->imageAdd(image, img, 1, 1);
        }
        else{
            operationDesc = tr("%1*image1 + %2*image2").arg(json["param1"].toDouble()).arg(json["param2"].toDouble());
            newImage = imageOperation->imageAdd(image, img, json["param1"].toDouble(), json["param2"].toDouble());
        }
        break;
    case AlgebraicDialog::SUBTRACT:
        if(json["default"].toBool()){
            operationDesc = "image1 - image2";
            newImage = imageOperation->imageSubtract(image, img, 1, 1);
        }
        else{
            operationDesc = tr("%1*image1 - %2*image2").arg(json["param1"].toDouble()).arg(json["param2"].toDouble());
            newImage = imageOperation->imageSubtract(image, img, json["param1"].toDouble(), json["param2"].toDouble());
        }
        break;
    case AlgebraicDialog::MULTIPLY:
        operationDesc = "image1 * image2";
        newImage = imageOperation->imageMultiply(image ,img);
        break;
    default:
        break;
    }
    makeCommit(image, "Algebraic Operation: " + operationDesc);
    updateImage(newImage);
}

void PhotoshopGUI::receiveApplyHSLAdjust(QJsonObject json, QImage img){
    QString desc = "HSL Adjust: ";
    desc += "Hue: (";
    QJsonArray hueValues = json["hueValues"].toArray();
    desc += "whole image: " + QString::number(hueValues[0].toInt()) + ", ";
    desc += "red: " + QString::number(hueValues[1].toInt()) + ", ";
    desc += "yellow: " + QString::number(hueValues[2].toInt()) + ", ";
    desc += "green: " + QString::number(hueValues[3].toInt()) + ", ";
    desc += "cyan: " + QString::number(hueValues[4].toInt()) + ", ";
    desc += "blue: " + QString::number(hueValues[5].toInt()) + ", ";
    desc += "magenta: " + QString::number(hueValues[6].toInt()) + "), ";
    desc += "Saturation: " + json["saturation"].toString() + ", ";
    desc += "Lightness: " + json["lightness"].toString();
    makeCommit(image, desc);
    updateImage(img);
}

void PhotoshopGUI::receiveApplyDualThreshold(QJsonObject json, QImage img){
    QString desc = "Image Binarization: DualThreshold: (low threshold: ";
    desc += json["low"].toString() + ", ";
    desc += "high threshold: " + json["high"].toString() + ")";
    makeCommit(image, desc);
    updateImage(img);
}

void PhotoshopGUI::receiveApplyScale(QJsonObject json){
    int type = json["algo"].toInt();
    int scale = json["scale"].toInt();
    int rotation = json["rotation"].toInt();
    QImage newImage;
    QString desc = "Scale/Rotation: Algorithms: ";
    if(type == 0){
        desc += "nearnest interpolation, ";
        newImage = imageOperation->nearnestInterpolation(image, scale, rotation);
    } else {
        desc += "bilinear interpolation, ";
        newImage = imageOperation->BilinearInterpolation(image, scale, rotation);
    }
    desc += "Scale: " + QString::number(scale) + ", ";
    desc += "Rotation: " + QString::number(rotation);
    makeCommit(image, desc);
    updateImage(newImage);
}

void PhotoshopGUI::receiveApplyFilter(QJsonObject json){
    setCursor(Qt::WaitCursor);
    QString desc = "Filter: Type: ";
    int type = json["type"].toInt();
    int col = json["col"].toInt();
    int row = json["row"].toInt();
    QImage newImage;
    int x = json["x"].toInt();
    int y = json["y"].toInt();
    if(type == 0){
        desc += "mean filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "))";
        newImage = imageOperation->meanFilter(image, col, row, x, y);
    } else if(type == 1){
        desc += "median filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "))";
        newImage = imageOperation->medianFilter(image, col, row, x, y);
    } else {
        double sigma = json["sigma"].toDouble();
        desc += "median filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "), ";
        desc += "Sigma: " + QString::number(sigma) + ")";
        newImage = imageOperation->gaussianFilter(image, col, row, x, y, sigma);
    }
    makeCommit(image, desc);
    updateImage(newImage);
    setCursor(Qt::ArrowCursor);
}

void PhotoshopGUI::receiveApplyEdgeDetection(QJsonObject json){
    setCursor(Qt::WaitCursor);
    QString desc = "Edge Detection: Type:";
    int type = json["type"].toInt();
    QImage newImage;
    if(type == 2){
        desc += "canny, ";
        int lo = json["lo"].toInt();
        int hi = json["hi"].toInt();
        desc += "Low Threshold: " + QString::number(lo) + ", ";
        desc += "High Threshold: " + QString::number(hi);
        newImage = imageOperation->cannyEdgeDetection(image, lo, hi);
    } else{
        int threshold = json["threshold"].toInt();
        if(type == 0){
            desc += "sobel, Threshold: " + QString::number(threshold);
            newImage = imageOperation->sobelEdgeDetection(image, threshold);
        } else {
            desc += "laplacian, Threshold: " + QString(threshold);
            newImage = imageOperation->laplacianEdgeDetection(image, threshold);
        }
    }
    makeCommit(image, desc);
    updateImage(newImage);
    setCursor(Qt::ArrowCursor);
}

void PhotoshopGUI::receiveApplyHoughTransform(QJsonObject json){
    setCursor(Qt::WaitCursor);
    QString desc = "Hough Transformation: Detect Circle: ";
    int lo = json["lo"].toInt();
    int hi = json["hi"].toInt();
    desc += "Radius: from " + QString::number(lo) + " to " + QString::number(hi);
    QImage newImage = imageOperation->houghCircleDetect(image, lo, hi);
    makeCommit(image, desc);
    updateImage(newImage);
    setCursor(Qt::ArrowCursor);
}

void PhotoshopGUI::receiveApplyClip(QJsonObject json){
    QString desc = "Clip: ";
    int left = json["left"].toInt();
    int right = json["right"].toInt();
    int top = json["top"].toInt();
    int bottom = json["bottom"].toInt();
    desc += "X: from " + QString::number(left) + " to " + QString::number(right) + ", ";
    desc += "Y: from " + QString::number(top) + " to " + QString::number(bottom);
    QImage newImage = imageOperation->clip(image, left, right, top, bottom);
    makeCommit(image, desc);
    updateImage(newImage);
}

void PhotoshopGUI::receiveApplyBinaryMorpho(QJsonObject json){
    QString desc = "Binary Morphology: Operation: ";
    int size = json["size"].toInt();
    QJsonArray elem = json["elem"].toArray();
    int *array = new int[size*size];
    //int array[size * size];
    for(int i = 0; i < size * size; i++){
        array[i] = elem[i].toInt();
    }
    int x = json["x"].toInt();
    int y = json["y"].toInt();
    QImage newImage;
    BinaryMorphoDialog::OperationType operation = (BinaryMorphoDialog::OperationType)json["operation"].toInt();
    switch (operation) {
    case BinaryMorphoDialog::DILATION:
        desc += "Dilation, ";
        newImage = imageOperation->dilation(image, size, x, y, array);
        break;
    case BinaryMorphoDialog::EROSION:
        desc += "Erosion, ";
        newImage = imageOperation->erosion(image, size, x, y, array);
        break;
    case BinaryMorphoDialog::OPENING:
        desc += "Opening, ";
        newImage = imageOperation->opening(image, size, x, y, array);
        break;
    case BinaryMorphoDialog::CLOSING:
        desc += "Closing, ";
        newImage = imageOperation->closing(image, size, x, y, array);
        break;
    case BinaryMorphoDialog::SKELETONIZATION:
        desc += "Skeletonization, ";
        newImage = imageOperation->skeletonization(image, size, x, y, array);
        break;
    case BinaryMorphoDialog::THINING:
        desc += "Thinning";
        newImage = imageOperation->thinning(image);
        break;
    case BinaryMorphoDialog::THICKING:
        desc += "Thicking";
        newImage = imageOperation->thicking(image);
        break;
    case BinaryMorphoDialog::DISTANCE_TRANSFORM:
        desc += "Distance Transform";
        newImage = imageOperation->distanceTransform(image);
        break;
    case BinaryMorphoDialog::SKELETON_RECONSTRUCTION:
        desc += "Skeleton Reconstruction, ";
        newImage = imageOperation->skeletionReconstruct(image, size, x, y, array);
        break;
    case BinaryMorphoDialog::RECONSTRUCTION:
        desc += "Reconstruction, ";
        newImage = imageOperation->binaryReconstruction(image, size, x, y, array);
        break;
    default:
        break;
    }
    if(operation != BinaryMorphoDialog::THINING
            && operation != BinaryMorphoDialog::THICKING
            && operation != BinaryMorphoDialog::DISTANCE_TRANSFORM){
        desc += tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
    }
    makeCommit(image, desc);
    updateImage(newImage);
    delete[] array;
}

void PhotoshopGUI::receiveApplyGrayMorpho(QJsonObject json){
    QString desc = "Grayscale Morphology: Operation: ";
    int size = json["size"].toInt();
    QJsonArray elem = json["elem"].toArray();
    int* array = new int[size*size];
    //int array[size * size];
    for(int i = 0; i < size * size; i++){
        array[i] = elem[i].toInt();
    }
    int x = json["x"].toInt();
    int y = json["y"].toInt();
    QImage newImage;
    GrayMorphoDialog::OperationType operation = (GrayMorphoDialog::OperationType)json["operation"].toInt();
    switch (operation) {
    case GrayMorphoDialog::DILATION:
        desc += "Dilation, ";
        newImage = imageOperation->dilation(image, size, x, y, array);
        break;
    case GrayMorphoDialog::EROSION:
        desc += "Erosion, ";
        newImage = imageOperation->erosion(image, size, x, y, array);
        break;
    case GrayMorphoDialog::OPENING:
        desc += "Opening, ";
        newImage = imageOperation->opening(image, size, x, y, array);
        break;
    case GrayMorphoDialog::CLOSING:
        desc += "Closing, ";
        newImage = imageOperation->closing(image, size, x, y, array);
        break;
    case GrayMorphoDialog::OBR:
        desc += "Opening By Reconstruction, ";
        newImage = imageOperation->obr(image, size, x, y, array);
        break;
    case GrayMorphoDialog::CBR:
        desc += "Closing By Reconstruction, ";
        newImage = imageOperation->cbr(image, size, x, y, array);
        break;
    case GrayMorphoDialog::WATERSHED:
        desc += "Watershed, ";
        newImage = imageOperation->watershed(image);
        break;
    default:
        break;
    }
    if(operation != GrayMorphoDialog::WATERSHED){
        desc += tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
    }
    makeCommit(image, desc);
    updateImage(newImage);
    delete[] array;
}

void PhotoshopGUI::receiveApplyCurve(QJsonObject json, QImage img){
    QString desc = "Adjust Contrast Curve: Curve Type: " + json["type"].toString();
    makeCommit(image, desc);
    updateImage(img);
}

void PhotoshopGUI::receiveApplyHistoEqualize(QImage img){
    makeCommit(image, tr("Histogram Equalization"));
    updateImage(img);
}

void PhotoshopGUI::receiveApplyLevelAdjust(QImage img){
    makeCommit(image, tr("Color Level Adjust"));
    updateImage(img);
}
