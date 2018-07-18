#ifndef OPENFILECOMMAND_H
#define OPENFILECOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ViewModel;

class OpenFileCommand
    : public ICommandBase
{
public:
    OpenFileCommand(ViewModel* vm);
    ~OpenFileCommand();
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
    std::string filepath;
};

#endif // OPENFILECOMMAND_H
