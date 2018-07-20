#include "LevelCommand.h"

LevelCommand::LevelCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void LevelCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void LevelCommand::Exec(){
    viewmodel->execLevelCommand(commandType);
    viewmodel->Fire_OnCommandComplete(LEVEL, true);
}
