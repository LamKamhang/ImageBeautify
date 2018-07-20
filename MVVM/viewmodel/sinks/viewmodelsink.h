#ifndef VIEWMODELSINK_H
#define VIEWMODELSINK_H

#include "../../common/etlbase.h"

class ViewModel;

class ViewModelSink: public IPropertyNotification
{
public:
    ViewModelSink(ViewModel *vm);
    virtual void OnPropertyChanged(const propertyType ppt);
private:
    ViewModel *viewmodel;
};

#endif // VIEWMODELSINK_H
