#include "LevelCommand.h"

LevelCommand::LevelCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void LevelCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void LevelCommand::Exec(){
    viewmodel->execLevelCommand(json);
    viewmodel->Fire_OnCommandComplete(LEVEL, true);
}
