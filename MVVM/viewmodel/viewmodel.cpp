#include "viewmodel.h"
#include "sinks/viewmodelsink.h"
#include "commands/openfilecommand.h"
#include "../common/util.h"
#include <QDebug>

ViewModel::ViewModel()
    : image(new QImage())
{
    viewModelSink = std::make_shared<ViewModelSink>(this);

    openfilecommand = std::make_shared<OpenFileCommand>(this);
    savefilecommand = std::make_shared<SaveFileCommand>(this);
    filtercommand = std::make_shared<FilterCommand>(this);
    edgedetectioncommand = std::make_shared<EdgeDetectionCommand>(this);
    houghcircledetectioncommand = std::make_shared<HoughCircleDetectionCommand>(this);
    channelcommand = std::make_shared<ChannelCommand>(this);
    grayscaletransfercommand = std::make_shared<GrayScaleTransferCommand>(this);
    otsucommand = std::make_shared<OtsuCommand>(this);
    houghlinedetectioncommand = std::make_shared<HoughLineDetectionCommand>(this);
}

void ViewModel::bindModel(std::shared_ptr<Model> model){
    this->model = model;
    model->AddPropertyNotification(std::static_pointer_cast<IPropertyNotification>(viewModelSink));
}

void ViewModel::execOpenFileCommand(std::string path){
    model->open_file(path);
}

void ViewModel::execSaveFileCommand(std::string path){
    model->save_file(path);
}

void ViewModel::execFilterCommand(const std::shared_ptr<JsonParameters>& json){
    qDebug() << "filter command";
    // model filter
    int type = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["type"])->getvalue();
    int col = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["col"])->getvalue();
    int row = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["row"])->getvalue();
    int x = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["x"])->getvalue();
    int y = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["y"])->getvalue();
    switch (type) {
    case 0:
        qDebug()<<"mean filter command";
//        model->meanFilter(col,row,x,y);
        break;
    case 1:
        qDebug()<<"median filter command";
//        model->medianFilter(col,row,x,y);
        break;
    case 2:
        qDebug()<<"guassian filter command";
        double sigma = std::static_pointer_cast<DoubleParameters,ParametersBase>((*json)["sigma"])->getvalue();
//        model->gaussianFilter(col,row,x,y,sigma);
        break;
    }
}

void ViewModel::execEdgeDetectionCommand(const std::shared_ptr<JsonParameters> &json){
    qDebug() << "edge detection command";
    // model edge detection
    int type = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["type"])->getvalue();
    if(type == 2){
        int lo = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["lo"])->getvalue();
        int hi = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["hi"])->getvalue();
        qDebug() << "canny detection command";
//        model->cannyEdgeDetection(lo,hi);
    } else {
        int threshold = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["threshold"])->getvalue();
        if(type == 0){
            qDebug() << "sobel detection command";
//            model->sobelEdgeDetection(threshold);
        } else {
            qDebug() << "laplacian detection command";
//            model->laplacianEdgeDetection(threshold);
        }
    }
}

void ViewModel::execHoughCircleDetectionCommand(const std::shared_ptr<JsonParameters> &json){
    qDebug() << "hough circle detection command";
    // model
    int lo = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["lo"])->getvalue();
    int hi = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["hi"])->getvalue();
//    model->houghCircleDetect(lo,hi);
}

void ViewModel::execChannelCommand(const std::shared_ptr<EnumCommandParameters> &type){
    switch (type->getvalue()) {
    case RED_CHANNEL:
        qDebug() << "red channel command";
        //model
        model->getSingleChannel(RED);
        break;
    case GREEN_CHANNEL:
        qDebug() << "green channel command";
//        model->getSingleChannel(GREEN);
        break;
    case BLUE_CHANNEL:
        qDebug() << "blue channel command";
//        model->getSingleChannel(BLUE);
        break;
    default:
        qDebug() << "error channel!";
        break;
    }
}

void ViewModel::execHoughLineDetectionCommand(){
    qDebug()<<"execHoughLineDetectionCommand()";
}

void ViewModel::execOtsuCommand(){
    qDebug()<<"execOtsuCommand()";
}

void ViewModel::execGrayScaleTransferCommand(){
    qDebug()<<"execGrayScaleTransferCommand()";
}

std::shared_ptr<ICommandBase> ViewModel::getOpenFileCommand(){
    return openfilecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getSaveFileCommand(){
    return savefilecommand;
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

std::shared_ptr<QImage> ViewModel::getImage(){
    return image;
}

void ViewModel::setImageFromModel(){
    *image = Tools::Mat2QImage(model->getMain());
}
