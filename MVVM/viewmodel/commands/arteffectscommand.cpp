#include "arteffectscommand.h"

ArtEffectsCommand::ArtEffectsCommand(ViewModel *vm)
    : viewmodel(vm)
{
}

void ArtEffectsCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void ArtEffectsCommand::Exec(){
    viewmodel->execArtEffectsCommand(json);
    viewmodel->Fire_OnCommandComplete(ART_EFFECTS,true);
}
