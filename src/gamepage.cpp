#include "gamepage.h"
#include <QMessageBox>

GamePage::GamePage(QWidget *parent, const QString &player1, const QString &player2)
    : QWidget(parent)
{
    QMessageBox::information(this, "شروع بازی",
                             QString("بازی بین %1 و %2 شروع شد!").arg(player1, player2));
}
