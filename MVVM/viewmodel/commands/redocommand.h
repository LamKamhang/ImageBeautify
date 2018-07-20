#ifndef REDOCOMMAND_H
#define REDOCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"
#include "../../common/type.h"

class RedoCommand
    : public ICommandBase
{
public:
    RedoCommand(ViewModel*vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
};

#endif // REDOCOMMAND_H
