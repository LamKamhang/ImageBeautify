#include "viewmodelsink.h"
#include "../viewmodel.h"

ViewModelSink::ViewModelSink(ViewModel *vm)
{
   viewmodel = vm;
}

void ViewModelSink::OnPropertyChanged(const propertyType ppt){
    if(ppt == MAIN_IMAGE){
        viewmodel->setImageFromModel();
    }

    viewmodel->Fire_OnPropertyChanged(ppt);
}
