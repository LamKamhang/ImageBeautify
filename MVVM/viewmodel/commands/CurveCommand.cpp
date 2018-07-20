#include "CurveCommand.h"

CurveCommand::CurveCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void CurveCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void CurveCommand::Exec(){
    viewmodel->execCurveCommand(commandType);
    viewmodel->Fire_OnCommandComplete(CURVE, true);
}
