#ifndef MAINIMAGESINK_H
#define MAINIMAGESINK_H

#include"../../common/etlbase.h"

class MainView;

class MainImageSink : public IPropertyNotification
{
public:
    MainImageSink(MainView *mainview);
    virtual void OnPropertyChanged(const std::string& str);

private:
    MainView * mainview;
}

#endif // MAINIMAGESINK_H
