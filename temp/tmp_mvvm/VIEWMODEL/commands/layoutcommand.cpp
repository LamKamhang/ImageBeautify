#include "layoutcommand.h"
#include "../swviewmodel.h"

layoutCommand::layoutCommand(SWViewModel *ptr_SWViewModel)
{
    ptr_SWViewModel_ = ptr_SWViewModel;
}

void layoutCommand::SetParameter(const std::shared_ptr<ParametersBase>& param)
{
    SWLevel = std::static_pointer_cast<IntParameters,ParametersBase>(param)->getvalue();
}

void layoutCommand::Exec()
{
    ptr_SWViewModel_->Exec_layout_command(SWLevel);
    ptr_SWViewModel_->Fire_OnCommandComplete("layoutCommand", true);
}
