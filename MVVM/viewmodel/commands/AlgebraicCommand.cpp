#include "AlgebraicCommand.h"

AlgebraicCommand::AlgebraicCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void AlgebraicCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void AlgebraicCommand::Exec(){
    viewmodel->execAlgebraicCommand(commandType);
    viewmodel->Fire_OnCommandComplete(ALGEBRAIC, true);
}
