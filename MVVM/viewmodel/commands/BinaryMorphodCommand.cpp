#include "BinaryMorphodCommand.h"

BinaryMorphodCommand::BinaryMorphodCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void BinaryMorphodCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void BinaryMorphodCommand::Exec(){
    viewmodel->execBinaryMorphodCommand(commandType);
    viewmodel->Fire_OnCommandComplete(BINARY_MORPHOD, true);
}
