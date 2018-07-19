#ifndef STARTBUTTONCOMMAND_H
#define STARTBUTTONCOMMAND_H
#include "../../common/etlbase.h"

class GameAPP;
class StartButtonCommand: public ICommandBase
{
private:
    GameAPP *ptrApp;
public:
    StartButtonCommand(GameAPP *ptr_App);
    ~StartButtonCommand();
    virtual void SetParameter(const std::shared_ptr<ParametersBase>& param);
    virtual void Exec();
};


#endif // STARTBUTTONCOMMAND_H
