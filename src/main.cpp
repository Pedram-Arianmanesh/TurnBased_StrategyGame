#include <QApplication>
#include "splashscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SplashScreen* splash = new SplashScreen();
    splash->show();

    return a.exec();
}
