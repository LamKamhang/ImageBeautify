#ifndef APP_H
#define APP_H

#include "../model/model.h"
#include "../viewmodel/viewmodel.h"
#include "../view/mainview.h"

class ImageBeautifyApp{
public:
    ImageBeautifyApp();
    ~ImageBeautifyApp();

    void run();

private:
    std::shared_ptr<MainView> view;
    std::shared_ptr<Model> model;
    std::shared_ptr<ViewModel> viewmodel;
};


#endif // APP_H
