#ifndef HOUGHLINEDETECTIONCOMMAND_H
#define HOUGHLINEDETECTIONCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class HoughLineDetectionCommand
    : public ICommandBase
{
public:
    HoughLineDetectionCommand(ViewModel *vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
};

#endif // HOUGHLINEDETECTIONCOMMAND_H
