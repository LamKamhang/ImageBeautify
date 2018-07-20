#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"
#include "../../common/type.h"

class UndoCommand
    : public ICommandBase
{
public:
    UndoCommand(ViewModel*vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
};

#endif // UNDOCOMMAND_H
