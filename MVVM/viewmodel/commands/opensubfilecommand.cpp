#include "opensubfilecommand.h"
#include "../viewmodel.h"
#include <QDebug>

OpenSubFileCommand::OpenSubFileCommand(ViewModel* vm)
    : viewmodel(vm)
{
}

void OpenSubFileCommand::SetParameter(const std::shared_ptr<ParametersBase> &param){
    qDebug()<<"OpenSubFileCommand::SetParameter";
    filepath = std::static_pointer_cast<QStringParameters,ParametersBase>(param)->getvalue();
    qDebug()<<"filepath = "<<filepath;
}

void OpenSubFileCommand::Exec(){
    qDebug()<<"OpenSubFileCommand::Exec";
    viewmodel->execOpenSubFileCommand(filepath);
    viewmodel->Fire_OnCommandComplete(OPEN_SUB_FILE,true);
}
