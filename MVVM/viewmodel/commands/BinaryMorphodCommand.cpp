#include "BinaryMorphodCommand.h"

BinaryMorphodCommand::BinaryMorphodCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void BinaryMorphodCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void BinaryMorphodCommand::Exec(){
    viewmodel->execBinaryMorphodCommand(json);
    viewmodel->Fire_OnCommandComplete(BINARY_MORPHOD, true);
}
