#include "HistogramCommand.h"

HistogramCommand::HistogramCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void HistogramCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void HistogramCommand::Exec(){
    viewmodel->execHistogramCommand(json);
    viewmodel->Fire_OnCommandComplete(HISTOGRAM, true);
}
