#include "BinaryMorphologyCommand.h"

BinaryMorphologyCommand::BinaryMorphologyCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void BinaryMorphologyCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void BinaryMorphologyCommand::Exec(){
    viewmodel->execBinaryMorphologyCommand(json);
    viewmodel->Fire_OnCommandComplete(BINARY_MORPHOLOGY, true);
}
