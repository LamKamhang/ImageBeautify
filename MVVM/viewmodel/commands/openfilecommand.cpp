#include "openfilecommand.h"
#include "../viewmodel.h"

OpenFileCommand::OpenFileCommand(ViewModel* vm)
    : viewmodel(vm)
{
}

void OpenFileCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    filepath = std::static_pointer_cast<QStringParameters,ParametersBase>(param)->getvalue();
}

void OpenFileCommand::Exec(){
    viewmodel->execOpenFileCommand(filepath);
    viewmodel->Fire_OnCommandComplete(OPEN_FILE,true);
}
