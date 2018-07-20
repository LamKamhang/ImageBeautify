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
    view->setUndoEnabled(viewmodel->getUndoEnabled());
    view->setRedoEnabled(viewmodel->getRedoEnabled());
    view->setUndoMsg(viewmodel->getUndoMsg());
    view->setRedoMsg(viewmodel->getRedoMsg());

    view->setOpenFileCommand(viewmodel->getOpenFileCommand());
    view->setSaveFileCommand(viewmodel->getSaveFileCommand());
    view->setOpenSubDialogCommand(viewmodel->getOpenSubDialogCommand());
    view->setRedoCommand(viewmodel->getRedoCommand());
    view->setUndoCommand(viewmodel->getUndoCommand());

    view->setFilterCommand(viewmodel->getFilterCommand());
    view->setEdgeDetectionCommand(viewmodel->getEdgeDetectionCommand());
    view->setHoughCircleDetectionCommand(viewmodel->getHoughCircleDetectionCommand());
    view->setChannelCommand(viewmodel->getChannelCommand());
    view->setOtsuCommand(viewmodel->getOtsuCommand());
    view->setGrayScaleTransferCommand(viewmodel->getGrayScaleTransferCommand());
    view->setHoughLineDetectionCommand(viewmodel->getHoughLineDetectionCommand());
    view->setDualThresholdCommand(viewmodel->getDualThresholdCommand());

    viewmodel->AddPropertyNotification(view->getMainViewSink());
}

void ImageBeautifyApp::run(){
    view->show();
}
