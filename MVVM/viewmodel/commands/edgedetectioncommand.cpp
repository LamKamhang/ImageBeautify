#include "edgedetectioncommand.h"
#include "../viewmodel.h"

EdgeDetectionCommand::EdgeDetectionCommand(ViewModel*vm)
    :viewmodel(vm)
{
}

void EdgeDetectionCommand::SetParameter(const std::shared_ptr<ParametersBase>& param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void EdgeDetectionCommand::Exec(){
    viewmodel->execEdgeDetectionCommand(json);
    viewmodel->Fire_OnCommandComplete(EDGE_DETECTION,true);
}
