#include "grayscaletransfercommand.h"

GrayScaleTransferCommand::GrayScaleTransferCommand(ViewModel*vm)
    :viewmodel(vm)
{
}

void GrayScaleTransferCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){

}

void GrayScaleTransferCommand::Exec(){
    viewmodel->execGrayScaleTransferCommand();
    viewmodel->Fire_OnCommandComplete(GRAY_SCALE_TRANSFER,true);
}
