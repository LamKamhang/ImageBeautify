#include "startbuttoncommand.h"
#include "../app.h"

StartButtonCommand::StartButtonCommand(GameAPP *ptr_App)
{
    ptrApp = ptr_App;
}
StartButtonCommand::~StartButtonCommand()
{}
void StartButtonCommand::SetParameter(const std::shared_ptr<ParametersBase>& param)
{}
void StartButtonCommand::Exec()
{
    (ptrApp->getStartPage())->close();
    (ptrApp->getGameWindow())->show();
}
