#ifndef EDGEDETECTIONCOMMAND_H
#define EDGEDETECTIONCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ViewModel;

class EdgeDetectionCommand
    : public ICommandBase
{
public:
    EdgeDetectionCommand(ViewModel* vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
    std::shared_ptr<JsonParameters> json;
};

#endif // EDGEDETECTIONCOMMAND_H
