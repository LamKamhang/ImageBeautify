#include "../viewmodel/photoshopgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGuiApplication::setApplicationDisplayName(PhotoshopGUI::tr("Image Beautify"));
    PhotoshopGUI w;
    w.show();

    return a.exec();
}
