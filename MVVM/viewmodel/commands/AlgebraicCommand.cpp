#include "AlgebraicCommand.h"

AlgebraicCommand::AlgebraicCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void AlgebraicCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void AlgebraicCommand::Exec(){
    viewmodel->execAlgebraicCommand(json);
    viewmodel->Fire_OnCommandComplete(ALGEBRAIC, true);
}
