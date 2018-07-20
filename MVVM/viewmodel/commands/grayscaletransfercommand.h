#ifndef GRAYSCALETRANSFERCOMMAND_H
#define GRAYSCALETRANSFERCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"
#include "../../common/type.h"

class GrayScaleTransferCommand
    : public ICommandBase
{
public:
    GrayScaleTransferCommand(ViewModel*vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
};

#endif // GRAYSCALETRANSFERCOMMAND_H
