#include <QApplication>
#include "app.h"

ImageBeautifyApp::ImageBeautifyApp()
    : view(new MainView)
    , model(new Model)
    , viewmodel(new ViewModel)
{
    viewmodel->bindModel(model);

    view->setImage(viewmodel->getImage());
    view->setSubImage(viewmodel->getSubImage());

    view->setOpenFileCommand(viewmodel->getOpenFileCommand());
    view->setSaveFileCommand(viewmodel->getSaveFileCommand());
    view->setOpenSubDialogCommand(viewmodel->getOpenSubDialogCommand());

    view->setFilterCommand(viewmodel->getFilterCommand());
    view->setEdgeDetectionCommand(viewmodel->getEdgeDetectionCommand());
    view->setHoughCircleDetectionCommand(viewmodel->getHoughCircleDetectionCommand());
    view->setChannelCommand(viewmodel->getChannelCommand());
    view->setOtsuCommand(viewmodel->getOtsuCommand());
    view->setGrayScaleTransferCommand(viewmodel->getGrayScaleTransferCommand());
    view->setHoughLineDetectionCommand(viewmodel->getHoughLineDetectionCommand());

    viewmodel->AddPropertyNotification(view->getMainViewSink());
}

void ImageBeautifyApp::run(){
    view->show();
}
