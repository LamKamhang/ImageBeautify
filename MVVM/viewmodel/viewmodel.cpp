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
    //    model->save_file(path);
}

void ViewModel::execEdgeDetectionCommand(const std::shared_ptr<JsonParameters> &json){
    qDebug() << "edge detection command";
    // model edge detection
}

void ViewModel::execHoughCircleDetectionCommand(const std::shared_ptr<JsonParameters> &json){
    qDebug() << "hough circle detection command";
    // model
}

void ViewModel::execChannelCommand(const std::shared_ptr<EnumCommandParameters> &type){
    switch (type->getvalue()) {
    case RED_CHANNEL:
        qDebug() << "red channel command";
        //model
        break;
    case GREEN_CHANNEL:
        qDebug() << "green channel command";
        break;
    case BLUE_CHANNEL:
        qDebug() << "blue channel command";
        break;
    default:
        qDebug() << "error channel!";
        break;
    }
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

std::shared_ptr<QImage> ViewModel::getImage(){
    return image;
}

void ViewModel::setImageFromModel(){
    *image = Tools::Mat2QImage(model->getShow());
}
