#include "CurveCommand.h"

CurveCommand::CurveCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void CurveCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void CurveCommand::Exec(){
    viewmodel->execCurveCommand(json);
    viewmodel->Fire_OnCommandComplete(CURVE, true);
}
