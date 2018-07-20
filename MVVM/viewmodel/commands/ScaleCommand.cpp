#include "ScaleCommand.h"

ScaleCommand::ScaleCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void ScaleCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void ScaleCommand::Exec(){
    viewmodel->execScaleCommand(commandType);
    viewmodel->Fire_OnCommandComplete(SCALE, true);
}
