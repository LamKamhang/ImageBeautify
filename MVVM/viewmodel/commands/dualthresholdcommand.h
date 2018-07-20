#ifndef DUALTHRESHOLDCOMMAND_H
#define DUALTHRESHOLDCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"
#include "../../common/type.h"

class ViewModel;

class DualThresholdCommand
    : public ICommandBase
{
public:
    DualThresholdCommand(ViewModel *vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel *viewmodel;
    std::shared_ptr<JsonParameters> json;
};

#endif // DUALTHRESHOLDCOMMAND_H
