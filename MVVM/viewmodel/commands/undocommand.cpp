#include "undocommand.h"

UndoCommand::UndoCommand(ViewModel*vm)
    :viewmodel(vm)
{
}

void UndoCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){

}

void UndoCommand::Exec(){
    viewmodel->execUndoCommand();
}
