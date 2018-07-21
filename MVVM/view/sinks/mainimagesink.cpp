#include "mainimagesink.h"
#include "../mainview.h"
#include "QDebug"

MainImageSink::MainImageSink(MainView *mainview)
    :mainview(mainview)
{
}

void MainImageSink::OnPropertyChanged(const propertyType pt)
{
    if(pt == MAIN_IMAGE){
        qDebug() << "in main image sink";
        mainview->update();
    } else if(pt == SUB_IMAGE){
        mainview->updateSubImage();
    } else if(pt == LOG){
        mainview->updateLogManager();
    }
}

