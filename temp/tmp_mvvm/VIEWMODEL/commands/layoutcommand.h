#ifndef LAYOUTCOMMAND_H
#define LAYOUTCOMMAND_H

#include "../../common/etlbase.h"


class SWViewModel;
class layoutCommand: public ICommandBase
{
public:
    layoutCommand(SWViewModel *ptr_SWViewModel);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    SWViewModel *ptr_SWViewModel_;
    int SWLevel;
};

#endif // LAYOUTCOMMAND_H
