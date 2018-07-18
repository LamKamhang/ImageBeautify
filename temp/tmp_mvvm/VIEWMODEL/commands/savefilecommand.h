#ifndef SAVEFILECOMMAND_H
#define SAVEFILECOMMAND_H
#include "../../common/etlbase.h"

class ViewModel;

class SaveFileCommand : public ICommandBase
{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    SaveFileCommand(std::shared_ptr<ViewModel> vm);
    void exec();
};

#endif // SAVEFILECOMMAND_H
