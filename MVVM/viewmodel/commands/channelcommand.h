#ifndef CHANNELCOMMAND_H
#define CHANNELCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"
#include "../../common/type.h"

class ViewModel;

class ChannelCommand
    : public ICommandBase
{
public:
    ChannelCommand(ViewModel* vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();

private:
    ViewModel* viewmodel;
    std::shared_ptr<EnumCommandParameters> commandType;
};

#endif // CHANNELCOMMAND_H
