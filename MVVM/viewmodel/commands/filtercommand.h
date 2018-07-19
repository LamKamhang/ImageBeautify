#ifndef FILTERCOMMAND_H
#define FILTERCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ViewModel;

class FilterCommand
    : public ICommandBase
{
public:
    FilterCommand(ViewModel* vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
    std::shared_ptr<JsonParameters> json;
};

#endif // FILTERCOMMAND_H
