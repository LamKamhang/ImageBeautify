#include "redocommand.h"

RedoCommand::RedoCommand(ViewModel*vm)
    :viewmodel(vm)
{
}

void RedoCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){

}

void RedoCommand::Exec(){
    viewmodel->execRedoCommand();
}
