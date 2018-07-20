#include "viewmodelsink.h"
#include "../viewmodel.h"

ViewModelSink::ViewModelSink(ViewModel *vm)
{
   viewmodel = vm;
}

void ViewModelSink::OnPropertyChanged(const propertyType ppt){
    if(ppt == MAIN_IMAGE){
        viewmodel->setImageFromModel();
    }else if(ppt == SUB_IMAGE){
        viewmodel->setSubImageFromModel();
    }else if(ppt == LOG){
        viewmodel->updateLogManagerFromModel();
    }
    viewmodel->Fire_OnPropertyChanged(ppt);
}
