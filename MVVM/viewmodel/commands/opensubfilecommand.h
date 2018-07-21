#ifndef OPENSUBFILECOMMAND_H
#define OPENSUBFILECOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ViewModel;

class OpenSubFileCommand
    : public ICommandBase
{
public:
    OpenSubFileCommand(ViewModel* vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
    QString filepath;
};

#endif // OPENSUBFILECOMMAND_H
