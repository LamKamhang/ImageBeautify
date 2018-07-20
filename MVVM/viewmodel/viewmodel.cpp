#include "viewmodel.h"
#include "sinks/viewmodelsink.h"
#include "commands/openfilecommand.h"
#include "../common/util.h"
#include <QDebug>

ViewModel::ViewModel()
    : image(new QImage())
    , subimage(new QImage())
    , undoEnabled(new bool(false))
    , redoEnabled(new bool(false))
    , undoMsg(new QString())
    , redoMsg(new QString())
{
    viewModelSink = std::make_shared<ViewModelSink>(this);

    openfilecommand = std::make_shared<OpenFileCommand>(this);
    savefilecommand = std::make_shared<SaveFileCommand>(this);
    opensubdialogcommand = std::make_shared<OpenSubDialogCommand>(this);

    filtercommand = std::make_shared<FilterCommand>(this);
    edgedetectioncommand = std::make_shared<EdgeDetectionCommand>(this);
    houghcircledetectioncommand = std::make_shared<HoughCircleDetectionCommand>(this);
    channelcommand = std::make_shared<ChannelCommand>(this);
    grayscaletransfercommand = std::make_shared<GrayScaleTransferCommand>(this);
    otsucommand = std::make_shared<OtsuCommand>(this);
    houghlinedetectioncommand = std::make_shared<HoughLineDetectionCommand>(this);
    dualthresholdcommand = std::make_shared<DualThresholdCommand>(this);
    undocommand = std::make_shared<UndoCommand>(this);
    redocommand = std::make_shared<RedoCommand>(this);
}

void ViewModel::bindModel(std::shared_ptr<Model> model){
    this->model = model;
    model->AddPropertyNotification(std::static_pointer_cast<IPropertyNotification>(viewModelSink));
}

void ViewModel::execOpenFileCommand(const QString &path){
    model->open_file(path);
}

void ViewModel::execSaveFileCommand(const QString &path){
    model->save_file(path);
}

void ViewModel::execOpenSubDialogCommand(){
    model->main2sub();
}

void ViewModel::execUndoCommand(){
    qDebug()<<"undo command";
    model->undo();
}

void ViewModel::execRedoCommand(){
    qDebug()<<"redo command";
    model->redo();
}

void ViewModel::execFilterCommand(std::shared_ptr<JsonParameters> json){
    qDebug() << "filter command";
    // model filter
    int type = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["type"])->getvalue();
    int col = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["col"])->getvalue();
    int row = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["row"])->getvalue();
    int x = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["x"])->getvalue();
    int y = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["y"])->getvalue();
    QString desc = "Filter: Type: ";
    switch (type) {
    case 0:
        qDebug()<<"mean filter command";
        desc += "mean filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "))";
        model->commit(desc);
        model->meanFilter(col,row,x,y);
        break;
    case 1:
        qDebug()<<"median filter command";
        desc += "median filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "))";
        model->commit(desc);
        model->medianFilter(col,row,x,y);
        break;
    case 2:
        qDebug()<<"guassian filter command";
        double sigma = std::static_pointer_cast<DoubleParameters,ParametersBase>((*json)["sigma"])->getvalue();
        desc += "median filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "), ";
        desc += "Sigma: " + QString::number(sigma) + ")";
        model->commit(desc);
        model->gaussianFilter(col,row,x,y,sigma);
        break;
    }
}

void ViewModel::execEdgeDetectionCommand(std::shared_ptr<JsonParameters> json){
    qDebug() << "edge detection command";
    // model edge detection
    int type = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["type"])->getvalue();
    QString desc = "Edge Detection: Type:";
    if(type == 2){
        int lo = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["lo"])->getvalue();
        int hi = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["hi"])->getvalue();
        qDebug() << "canny detection command";
        desc += "canny, ";
        desc += "Low Threshold: " + QString::number(lo) + ", ";
        desc += "High Threshold: " + QString::number(hi);
        model->commit(desc);
        model->cannyEdgeDetection(lo,hi);
    } else {
        int threshold = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["threshold"])->getvalue();
        if(type == 0){
            qDebug() << "sobel detection command";
            desc += "sobel, Threshold: " + QString::number(threshold);
            model->commit(desc);
            model->sobelEdgeDetection(threshold);
        } else {
            qDebug() << "laplacian detection command";
            desc += "laplacian, Threshold: " + QString(threshold);
            model->commit(desc);
            model->laplacianEdgeDetection(threshold);
        }
    }
}

void ViewModel::execHoughCircleDetectionCommand(std::shared_ptr<JsonParameters>json){
    qDebug() << "hough circle detection command";
    QString desc = "Hough Transformation: Detect Circle: ";
    int lo = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["lo"])->getvalue();
    int hi = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["hi"])->getvalue();
    desc += "Radius: from " + QString::number(lo) + " to " + QString::number(hi);
    model->commit(desc);
    model->houghCircleDetect(lo,hi);
}

void ViewModel::execChannelCommand(std::shared_ptr<EnumCommandParameters> type){
    switch (type->getvalue()) {
    case RED_CHANNEL:
        qDebug() << "red channel command";
        //model
        model->commit("Channel Separation: Red");
        model->getSingleChannel(RED);
        break;
    case GREEN_CHANNEL:
        qDebug() << "green channel command";
        model->commit("Channel Separation: Green");
        model->getSingleChannel(GREEN);
        break;
    case BLUE_CHANNEL:
        qDebug() << "blue channel command";
        model->commit("Channel Separation: Blue");
        model->getSingleChannel(BLUE);
        break;
    default:
        qDebug() << "error channel!";
        break;
    }
}

void ViewModel::execHoughLineDetectionCommand(){
    qDebug()<<"execHoughLineDetectionCommand()";
    //    qDebug()<<"bug here";
    //    model->houghLineDetect();
}

void ViewModel::execOtsuCommand(){
    qDebug()<<"execOtsuCommand()";
    model->commit("Image Binarization: OTSU");
    model->otsu();
}

void ViewModel::execGrayScaleTransferCommand(){
    qDebug()<<"execGrayScaleTransferCommand()";
    model->commit("Gray-Scale Transfer");
    model->grayScale();
}

void ViewModel::execDualThresholdCommand(std::shared_ptr<JsonParameters> json){
    qDebug()<<"execDualThresholdCommand(std::shared_ptr<JsonParameters> json)";
    bool apply = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["apply"])->getvalue();
    int lo = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["low"])->getvalue();
    int hi = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["high"])->getvalue();
    qDebug()<<"low = "<<lo <<"high = "<<hi;
    model->dualThreshold(lo,hi);
    if(apply){
        QString desc = "Image Binarization: DualThreshold: (low threshold: ";
        desc += QString::number(lo) + ", ";
        desc += "high threshold: " + QString::number(hi) + ")";
        model->commit(desc);
        model->sub2main();
    }
}

std::shared_ptr<ICommandBase> ViewModel::getOpenFileCommand(){
    return openfilecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getSaveFileCommand(){
    return savefilecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getOpenSubDialogCommand(){
    return opensubdialogcommand;
}

std::shared_ptr<ICommandBase> ViewModel::getUndoCommand(){
    return undocommand;
}

std::shared_ptr<ICommandBase> ViewModel::getRedoCommand(){
    return redocommand;
}

std::shared_ptr<ICommandBase> ViewModel::getFilterCommand(){
    return filtercommand;
}

std::shared_ptr<ICommandBase> ViewModel::getEdgeDetectionCommand(){
    return edgedetectioncommand;
}

std::shared_ptr<ICommandBase> ViewModel::getHoughCircleDetectionCommand(){
    return houghcircledetectioncommand;
}

std::shared_ptr<ICommandBase> ViewModel::getChannelCommand(){
    return channelcommand;
}

std::shared_ptr<ICommandBase> ViewModel::getOtsuCommand(){
    return otsucommand;
}

std::shared_ptr<ICommandBase> ViewModel::getHoughLineDetectionCommand(){
    return houghlinedetectioncommand;
}

std::shared_ptr<ICommandBase> ViewModel::getGrayScaleTransferCommand(){
    return grayscaletransfercommand;
}

std::shared_ptr<ICommandBase> ViewModel::getDualThresholdCommand(){
    return dualthresholdcommand;
}


std::shared_ptr<QImage> ViewModel::getImage(){
    return image;
}

std::shared_ptr<QImage> ViewModel::getSubImage(){
    return subimage;
}

std::shared_ptr<bool> ViewModel::getUndoEnabled(){
    return undoEnabled;
}
std::shared_ptr<bool> ViewModel::getRedoEnabled(){
    return redoEnabled;
}
std::shared_ptr<QString> ViewModel::getUndoMsg(){
    return undoMsg;
}
std::shared_ptr<QString> ViewModel::getRedoMsg(){
    return redoMsg;
}

void ViewModel::setImageFromModel(){
    *image = model->getMain();
}

void ViewModel::setSubImageFromModel(){
    *subimage = model->getSub();
}

void ViewModel::updateLogManagerFromModel(){
    *undoEnabled = model->undoEnabled();
    *redoEnabled = model->redoEnabled();
    *undoMsg = model->getUndoMsg();
    *redoMsg = model->getRedoMsg();
}
