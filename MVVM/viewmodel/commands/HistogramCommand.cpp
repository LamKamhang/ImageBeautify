#include "HistogramCommand.h"

HistogramCommand::HistogramCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void HistogramCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    commandType = std::static_pointer_cast<EnumCommandParameters,ParametersBase>(param);
}

void HistogramCommand::Exec(){
    viewmodel->execHistogramCommand(commandType);
    viewmodel->Fire_OnCommandComplete(HISTOGRAM, true);
}
