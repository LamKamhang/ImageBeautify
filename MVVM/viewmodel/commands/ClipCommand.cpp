#include "ClipCommand.h"

ClipCommand::ClipCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void ClipCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void ClipCommand::Exec(){
    viewmodel->execClipCommand(commandType);
    viewmodel->Fire_OnCommandComplete(BINARY_MCLIPORPHOD, true);
}
