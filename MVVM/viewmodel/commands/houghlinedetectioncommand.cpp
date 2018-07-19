#include "houghlinedetectioncommand.h"

HoughLineDetectionCommand::HoughLineDetectionCommand(ViewModel*vm)
    : viewmodel(vm)
{
}

void HoughLineDetectionCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){

}

void HoughLineDetectionCommand::Exec(){
    viewmodel->execHoughLineDetectionCommand();
    viewmodel->Fire_OnCommandComplete(HOUGH_LINE_DETECTION,true);
}
