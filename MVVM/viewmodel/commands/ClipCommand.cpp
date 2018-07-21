#include "ClipCommand.h"

ClipCommand::ClipCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void ClipCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void ClipCommand::Exec(){
    viewmodel->execClipCommand(json);
    viewmodel->Fire_OnCommandComplete(CLIP, true);
}
