#include "splashscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SplashScreen splash;
    splash.show();
    return a.exec();
}
