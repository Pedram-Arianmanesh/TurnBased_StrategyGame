#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include "ui_splashscreen.h"

class SplashScreen : public QWidget {
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = nullptr);

private slots:
    void goToMenu();

private:
    Ui::SplashScreen *ui;
};

#endif
