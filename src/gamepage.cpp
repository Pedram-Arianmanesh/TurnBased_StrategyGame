#include "gamepage.h"
#include <QVBoxLayout>
#include <QLabel>

GamePage::GamePage(QWidget *parent, const QString &player1, const QString &player2)
    : QWidget(parent)
{
    setWindowTitle("Game Page");
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label1 = new QLabel("Player 1: " + player1);
    QLabel *label2 = new QLabel("Player 2: " + player2);

    layout->addWidget(label1);
    layout->addWidget(label2);
}
