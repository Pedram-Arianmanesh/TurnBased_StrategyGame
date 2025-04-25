#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include "ui_playerdialog.h"

class PlayerDialog : public QDialog {
    Q_OBJECT

public:
    explicit PlayerDialog(QWidget *parent = nullptr);
    QString player1Name() const;
    QString player2Name() const;

private slots:
    void onStartClicked();

private:
    Ui::PlayerDialog *ui;
};

#endif // PLAYERDIALOG_H
