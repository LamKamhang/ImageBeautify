#include "Commands/open_file_command.h"
#include "ViewModel/viewmodel.h"
#include "command.h"
#include <QDebug>
#include <string>


OpenFileCommand::OpenFileCommand(ViewModel* vm)
    :viewmodel(vm)
{
}

OpenFileCommand::~OpenFileCommand(){}

void OpenFileCommand::exec(){
    std::string path = std::static_pointer_cast<PathParameters, Parameters>(Command::params)->get_path();
    viewmodel->exec_open_file_command(path);
}


