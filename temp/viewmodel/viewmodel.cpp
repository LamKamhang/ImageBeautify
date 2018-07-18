#include "viewmodel.h"
#include "sinks/viewmodelsink.h"
#include "commands/openfilecommand.h"
#include "../common/util.h"

ViewModel::ViewModel()
    : image(new QImage())
{
    viewModelSink = std::make_shared<ViewModelSink>(this);
    openfilecommand = std::make_shared<OpenFileCommand>(this);
    savefilecommand = std::make_shared<SaveFileCommand>(this);
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

std::shared_ptr<ICommandBase> ViewModel::getOpenFileCommand(){
    return openfilecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getSaveFileCommand(){
    return savefilecommand;
}

std::shared_ptr<QImage> ViewModel::getImage(){
    return image;
}

void ViewModel::setImageFromModel(){
    *image = Tools::Mat2QImage(model->getShow());
}
