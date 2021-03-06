#ifndef OTSUCOMMAND_H
#define OTSUCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"
#include "../../common/type.h"

class OtsuCommand
    : public ICommandBase
{
public:
    OtsuCommand(ViewModel*vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
};

#endif // OTSUCOMMAND_H
