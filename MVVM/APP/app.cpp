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

    viewmodel->AddPropertyNotification(view->getMainViewSink());
}

void ImageBeautifyApp::run(){
    view->show();
}

//void GameAPP::run()
//{
//    model = std::make_shared<Model>();
//    viewmodel = std::make_shared<SWViewModel>();

//    viewmodel->setSWModel(model);


//    window2.set_ptrCommand(viewmodel->getLayoutCommand());
//    window2.set_ptrMouseMoveCommand(viewmodel->getMouseMoveCommand());
//    window2.set_Martix(viewmodel->getSWMatrix());
//    viewmodel->AddPropertyNotification(window2.getPtrWindowProSink());
//    viewmodel->AddCommandNotification(window2.getPtrWindowSetSink());
//    viewmodel->AddCommandNotification(window2.getPtrMouseMoveCommandSink());

//    sp_StartButtonCommand_ = std::make_shared<StartButtonCommand>(this);

//    window1.set_ptrCommand(std::static_pointer_cast<ICommandBase>(this->sp_StartButtonCommand_));
//    window1.show();



//}
//startpage* GameAPP::getStartPage()
//{
//    return &window1;
//}
//gamewindow* GameAPP::getGameWindow()
//{
//    return &window2;
//}

