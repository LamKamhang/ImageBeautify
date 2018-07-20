#include "houghcircledetectioncommand.h"
#include "../viewmodel.h"

HoughCircleDetectionCommand::HoughCircleDetectionCommand(ViewModel*vm)
    : viewmodel(vm)
{
}

void HoughCircleDetectionCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    json = std::static_pointer_cast<JsonParameters,ParametersBase>(param);
}

void HoughCircleDetectionCommand::Exec(){
    viewmodel->execHoughCircleDetectionCommand(json);
    viewmodel->Fire_OnCommandComplete(HOUGH_CIRCLE_DETECTION,true);
}
