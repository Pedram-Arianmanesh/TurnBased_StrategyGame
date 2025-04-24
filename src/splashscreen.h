#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>

namespace Ui {
class SplashScreen;
}

class SplashScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();

signals:
    void startClicked();

private slots:
    void onStartButtonClicked();

private:
    Ui::SplashScreen *ui;
};

#endif
