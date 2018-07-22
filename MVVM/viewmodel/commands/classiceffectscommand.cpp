#include "classiceffectscommand.h"

ClassicEffectsCommand::ClassicEffectsCommand(ViewModel *vm)
    : viewmodel(vm)
{
}

void ClassicEffectsCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void ClassicEffectsCommand::Exec(){
    viewmodel->execClassicEffectsCommand(json);
    viewmodel->Fire_OnCommandComplete(CLASSIC_EFFECTS,true);
}
