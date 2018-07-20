#ifndef OPENSUBDIALOGCOMMAND_H
#define OPENSUBDIALOGCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"
#include "../../common/type.h"

class OpenSubDialogCommand
    : public ICommandBase
{
public:
    OpenSubDialogCommand(ViewModel *vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel *viewmodel;
};

#endif // OPENSUBDIALOGCOMMAND_H
