#ifndef CLASSICEFFECTSCOMMAND_H
#define CLASSICEFFECTSCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ClassicEffectsCommand : public ICommandBase
{
public:
    ClassicEffectsCommand(ViewModel*vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase> &param);
    virtual void Exec();

private:
    ViewModel *viewmodel;
    std::shared_ptr<JsonParameters> json;
};

#endif // CLASSICEFFECTSCOMMAND_H
