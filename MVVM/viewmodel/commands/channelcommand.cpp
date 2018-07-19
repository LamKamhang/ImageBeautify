#include "channelcommand.h"

ChannelCommand::ChannelCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void ChannelCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void ChannelCommand::Exec(){
    viewmodel->execChannelCommand(commandType);
    viewmodel->Fire_OnCommandComplete(CHANNEL,true);
}
