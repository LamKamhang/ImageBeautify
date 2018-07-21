#include "GrayMorphologyCommand.h"

GrayMorphologyCommand::GrayMorphologyCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void GrayMorphologyCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void GrayMorphologyCommand::Exec(){
    viewmodel->execGrayMorphologyCommand(json);
    viewmodel->Fire_OnCommandComplete(GRAY_MORPHOLOGY, true);
}
