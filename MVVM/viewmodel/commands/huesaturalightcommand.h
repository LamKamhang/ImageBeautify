#ifndef HUESATURALIGHTCOMMAND_H
#define HUESATURALIGHTCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"
#include "../../common/type.h"

class ViewModel;

class HueSaturaLightCommand
    : public ICommandBase
{
public:
    HueSaturaLightCommand(ViewModel *vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel *viewmodel;
    std::shared_ptr<JsonParameters> json;
};

#endif // HUESATURALIGHTCOMMAND_H
