#ifndef HOUGHCIRCLEDETECTIONCOMMAND_H
#define HOUGHCIRCLEDETECTIONCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ViewModel;

class HoughCircleDetectionCommand
    : public ICommandBase
{

public:
    HoughCircleDetectionCommand(ViewModel* vm);

    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
    std::shared_ptr<JsonParameters> json;

};

#endif // HOUGHCIRCLEDETECTIONCOMMAND_H
