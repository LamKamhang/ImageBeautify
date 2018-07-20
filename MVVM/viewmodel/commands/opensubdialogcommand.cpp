#include "opensubdialogcommand.h"

OpenSubDialogCommand::OpenSubDialogCommand(ViewModel *vm)
    :viewmodel(vm)
{
}

OpenSubDialogCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){

}

OpenSubDialogCommand::Exec(){
    viewmodel->execOpenSubDialogCommand();
}
