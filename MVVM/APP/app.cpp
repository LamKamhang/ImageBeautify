#include <QApplication>
#include "app.h"

ImageBeautifyApp::ImageBeautifyApp()
    : view(new MainView)
    , model(new Model)
    , viewmodel(new ViewModel)
{
    viewmodel->bindModel(model);

    view->setImage(viewmodel->getImage());
    view->setOpenFileCommand(viewmodel->getOpenFileCommand());
    view->setSaveFileCommand(viewmodel->getSaveFileCommand());
    view->setFilterCommand(viewmodel->getFilterCommand());
    view->setEdgeDetectionCommand(viewmodel->getEdgeDetectionCommand());
    view->setHoughCircleDetectionCommand(viewmodel->getHoughCircleDetectionCommand());
    view->setChannelCommand(viewmodel->getChannelCommand());

    viewmodel->AddPropertyNotification(view->getMainViewSink());
}

void ImageBeautifyApp::run(){
    view->show();
}
