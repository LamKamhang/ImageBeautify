#include "HistogramCommand.h"

HistogramCommand::HistogramCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

void HistogramCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    histo = std::static_pointer_cast<VectorParameters<int>,ParametersBase>(param);
}

void HistogramCommand::Exec(){
    viewmodel->execHistogramCommand(histo);
    viewmodel->Fire_OnCommandComplete(HISTOGRAM, true);
}
