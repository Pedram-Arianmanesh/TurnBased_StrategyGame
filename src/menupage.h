#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>
#include "ui_menupage.h"

class MenuPage : public QWidget {
    Q_OBJECT

public:
    explicit MenuPage(QWidget *parent = nullptr);

private slots:
    void onGalleryClicked();
    void onStartPvPClicked();

private:
    Ui::MenuPage *ui;
};

#endif
