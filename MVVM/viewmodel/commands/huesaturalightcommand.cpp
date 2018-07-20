#include "huesaturalightcommand.h"

HueSaturaLightCommand::HueSaturaLightCommand(ViewModel *vm)
    :viewmodel(vm)
{
}

void HueSaturaLightCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void HueSaturaLightCommand::Exec(){
    viewmodel->execHueSaturaLightCommand(json);
    viewmodel->Fire_OnCommandComplete(HUE_SATURA_LIGHT,true);
}
