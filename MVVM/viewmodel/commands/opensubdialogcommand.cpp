#include "opensubdialogcommand.h"

OpenSubDialogCommand::OpenSubDialogCommand(ViewModel *vm)
    :viewmodel(vm)
{
}

void OpenSubDialogCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){

}

void OpenSubDialogCommand::Exec(){
    viewmodel->execOpenSubDialogCommand();
    viewmodel->Fire_OnCommandComplete(OPEN_SUB_DIALOG,true);
}
