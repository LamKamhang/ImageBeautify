#include "GrayMorphodCommand.h"

GrayMorphodCommand::GrayMorphodCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void GrayMorphodCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void GrayMorphodCommand::Exec(){
    viewmodel->execGrayMorphodCommand(commandType);
    viewmodel->Fire_OnCommandComplete(GRAY_MORPHOD, true);
}
