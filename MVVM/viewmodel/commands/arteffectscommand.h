#ifndef ARTEFFECTSCOMMAND_H
#define ARTEFFECTSCOMMAND_H
#include "../../common/etlbase.h"
#include "viewmodel/viewmodel.h"
#include "../../common/parameters.h"

class ArtEffectsCommand : public ICommandBase
{
public:
    ArtEffectsCommand(ViewModel*vm);
    virtual void SetParameter(const std::shared_ptr<ParametersBase> &param);
    virtual void Exec();

private:
    ViewModel *viewmodel;
    std::shared_ptr<JsonParameters> json;
};

#endif // ARTEFFECTSCOMMAND_H
