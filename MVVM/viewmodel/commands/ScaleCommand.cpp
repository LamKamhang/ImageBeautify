#include "ScaleCommand.h"

ScaleCommand::ScaleCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void ScaleCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void ScaleCommand::Exec(){
    viewmodel->execScaleCommand(json);
    viewmodel->Fire_OnCommandComplete(SCALE, true);
}
