#include "splashscreen.h"
#include "ui_splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SplashScreen)
{
    ui->setupUi(this);

    connect(ui->StartButton, &QPushButton::clicked, this, &SplashScreen::onStartButtonClicked);
}

SplashScreen::~SplashScreen()
{
    delete ui;
}

void SplashScreen::onStartButtonClicked()
{
    emit startClicked();
}
