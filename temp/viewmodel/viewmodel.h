#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QImage>
#include <memory>
#include "../model/model.h"
#include "../common/etlbase.h"
#include "../common/type.h"
#include "commands/openfilecommand.h"
#include "commands/savefilecommand.h"
#include "sinks/viewmodelsink.h"
#include <opencv2/opencv.hpp>
using namespace cv;

class OpenFileCommand;
class SaveFileCommand;

class ViewModel
    : public Proxy_PropertyNotification<ViewModel>
    , public Proxy_CommandNotification<ViewModel>
{
public:
    ViewModel();
    ~ViewModel(){}
    void bindModel(std::shared_ptr<Model> model);// binding model
    void execOpenFileCommand(std::string path);
    void execSaveFileCommand(std::string path);

    std::shared_ptr<ICommandBase> getOpenFileCommand();
    std::shared_ptr<ICommandBase> getSaveFileCommand();

    std::shared_ptr<QImage> getImage();
    void setImageFromModel();

private:
    std::shared_ptr<QImage> image;
    std::shared_ptr<Model> model;

    std::shared_ptr<ViewModelSink> viewModelSink;

    std::shared_ptr<OpenFileCommand> openfilecommand;
    std::shared_ptr<SaveFileCommand> savefilecommand;
};



#endif // VIEWMODEL_H
