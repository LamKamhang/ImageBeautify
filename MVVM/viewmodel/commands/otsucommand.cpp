#include "otsucommand.h"

OtsuCommand::OtsuCommand(ViewModel*vm)
    :viewmodel(vm)
{
}

void OtsuCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){

}

void OtsuCommand::Exec(){
    viewmodel->execOtsuCommand();
    viewmodel->Fire_OnCommandComplete(OTSU,true);
}

