#ifndef MAINCOMMANDSINK_H
#define MAINCOMMANDSINK_H

#include"../../common/etlbase.h"

class MainView;

class MainCommandSink : public ICommandNotification
{
public:
    MainCommandSink(MainView *mainview);
    virtual void OnCommandComplete(const commandsType cmd, bool OK);

private:
    MainView * mainview;
};

#endif // MAINCOMMANDSINK_H
