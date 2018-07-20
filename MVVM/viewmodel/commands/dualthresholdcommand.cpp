#include "dualthresholdcommand.h"

DualThresholdCommand::DualThresholdCommand(ViewModel*vm)
    :viewmodel(vm)
{
}


void DualThresholdCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void DualThresholdCommand::Exec(){
    viewmodel->execDualThresholdCommand(json);
    viewmodel->Fire_OnCommandComplete(DUAL_THRESHOLD,true);
}
