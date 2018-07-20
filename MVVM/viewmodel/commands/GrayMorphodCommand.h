#pragma once
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ViewModel;

class GrayMorphodCommand
    : public ICommandBase
{
public:
    GrayMorphodCommand(ViewModel* vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
    std::shared_ptr<JsonParameters> json;
};
