#include <QApplication>
#include "app/app.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageBeautifyApp *app = new ImageBeautifyApp;
    app->run();
    return a.exec();
}
