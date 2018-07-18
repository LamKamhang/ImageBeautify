#include "openfilecommand.h"
#include "../viewmodel.h"

OpenFileCommand::OpenFileCommand(std::shared_ptr<ViewModel> vm)
    : viewmodel(vm)
{

}

OpenFileCommand::exec(){
    std::string path =
    std::static_pointer_cast<PathParameters, Parameters>(Command::params)->get_path();
    viewmodel->execOpenFileCommand(path);
}
