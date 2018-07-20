#include "mainimagesink.h"
#include "../mainview.h"

MainImageSink::MainImageSink(MainView *mainview)
    :mainview(mainview)
{
}

void MainImageSink::OnPropertyChanged(const propertyType pt)
{
    if(pt == MAIN_IMAGE){
        mainview->update();
    } else if(pt == SUB_IMAGE){
        mainview->updateSubImage();
    } else if(pt == LOG){
        mainview->updateLogManager();
    }
}

