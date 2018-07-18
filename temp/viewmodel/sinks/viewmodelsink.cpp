#include "viewmodelsink.h"
#include "../viewmodel.h"

ViewModelSink::ViewModelSink(ViewModel *vm)
{
   viewmodel = vm;
}

void ViewModelSink::OnPropertyChanged(const std::string& str){
    viewmodel->Fire_OnPropertyChanged(str);
}
