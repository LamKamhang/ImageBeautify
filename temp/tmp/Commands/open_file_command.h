#ifndef _OPEN_FILE_COMMAND_H_
#define _OPEN_FILE_COMMAND_H_

#include "command.h"
#include "ViewModel/viewmodel.h"
#include <string>
#include <memory>

class OpenFileCommand : public Command{
private:
    ViewModel* viewmodel;
public:
    OpenFileCommand(ViewModel* vm);
    ~OpenFileCommand();
    void exec();

};

#endif
