#ifndef SAVEFILECOMMAND_H
#define SAVEFILECOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ViewModel;

class SaveFileCommand
    : public ICommandBase
{
public:
    SaveFileCommand(ViewModel* vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase> &param);
    virtual void Exec();
private:
    ViewModel* viewmodel;
    QString filepath;
};

#endif // SAVEFILECOMMAND_H
