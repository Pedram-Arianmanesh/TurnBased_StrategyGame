#include "gamepage.h"
#include "hexboardwidget.h"
#include <QVBoxLayout>
#include <QDebug>

GamePage::GamePage(QWidget *parent,
                   const QString &player1,
                   const QString &player2)
    : QWidget(parent),
    m_player1(player1),
    m_player2(player2)
{
    setWindowTitle("Tactical Monsters - Game");
    resize(1280, 800);
    setupUI();
}

void GamePage::setupUI()
{
    Board board = BoardParser::parseBoard(":/maps/grid1.txt");

    if (board.empty()) {
        qWarning() << "❗ Board is empty. Check your map file path!";
    }

    HexBoardWidget *boardWidget = new HexBoardWidget(board, this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(boardWidget);
    setLayout(layout);
}


