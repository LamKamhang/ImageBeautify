#include "savefilecommand.h"
#include "../viewmodel.h"

SaveFileCommand::SaveFileCommand(ViewModel* vm)
    : viewmodel(vm)
{
}

void SaveFileCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    filepath = std::static_pointer_cast<QStringParameters,ParametersBase>(param)->getvalue();
}

void SaveFileCommand::Exec(){
    viewmodel->execSaveFileCommand(filepath);
    viewmodel->Fire_OnCommandComplete(SAVE_FILE,true);
}
