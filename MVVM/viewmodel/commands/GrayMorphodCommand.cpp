#include "GrayMorphodCommand.h"

GrayMorphodCommand::GrayMorphodCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void GrayMorphodCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void GrayMorphodCommand::Exec(){
    viewmodel->execGrayMorphodCommand(json);
    viewmodel->Fire_OnCommandComplete(GRAY_MORPHOD, true);
}
