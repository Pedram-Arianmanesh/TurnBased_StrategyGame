#include "splashscreen.h"
#include "menupage.h"

SplashScreen::SplashScreen(QWidget *parent)
    : QWidget(parent), ui(new Ui::SplashScreen)
{
    ui->setupUi(this);

    connect(ui->StartButton, &QPushButton::clicked, this, &SplashScreen::goToMenu);
}

void SplashScreen::goToMenu() {
    MenuPage *menu = new MenuPage();
    menu->show();
    this->close();
}
