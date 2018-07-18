#ifndef OPENFILECOMMAND_H
#define OPENFILECOMMAND_H
#include "../../common/etlbase.h"
#include "VIEWMODEL/viewmodel.h"

class OpenFileCommand : public ICommandBase{
private:
    std::shared_ptr<ViewModel> viewmodel;
public:
    OpenFileCommand(std::shared_ptr<ViewModel> vm);
    ~OpenFileCommand();
    void exec();
};

#endif // OPENFILECOMMAND_H
