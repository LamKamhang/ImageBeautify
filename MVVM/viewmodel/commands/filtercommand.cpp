#include "filtercommand.h"
#include "../viewmodel.h"

FilterCommand::FilterCommand(ViewModel*vm)
    :viewmodel(vm)
{
}

void FilterCommand::SetParameter(const std::shared_ptr<ParametersBase>& param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void FilterCommand::Exec(){
    viewmodel->execFilterCommand(json);
    viewmodel->Fire_OnCommandComplete(FILTER,true);
}
