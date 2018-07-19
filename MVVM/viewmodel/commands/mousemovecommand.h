#ifndef MOUSEMOVECOMMAND_H
#define MOUSEMOVECOMMAND_H

#include "../../common/etlbase.h"

class SWViewModel;

class mouseMoveCommand: public ICommandBase
{
public:
    mouseMoveCommand(SWViewModel *ptr_SWViewModel);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    SWViewModel *ptr_SWViewModel_;
    int mouseOnRow;
    int mouseOnCol;
};

#endif // MOUSEMOVECOMMAND_H
