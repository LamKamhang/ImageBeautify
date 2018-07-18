#include "mainimagesink.h"
#include "../mainview.h"

MainImageSink::MainImageSink(MainView *mainview)
    :mainview(mainview)
{

}

void MainImageSink::OnPropertyChanged(const std::string &str)
{
    if(str == "mainimage"){
        mainview->update();
    }
}

