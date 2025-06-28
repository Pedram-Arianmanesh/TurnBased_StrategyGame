#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QString>
#include <vector>

#include "logic/gameboard.h"
#include "hexboardwidget.h"
#include "logic/agent.h"
#include "agentcard.h"

namespace Ui {
class GamePage;
}

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr, const QString &player1 = "", const QString &player2 = "");
    ~GamePage();



private:
    Ui::GamePage *ui;

    QString m_player1;
    QString m_player2;

    GameBoard* m_gameBoard;
    HexBoardWidget* m_boardWidget;


    std::vector<Agent*> m_player1AgentPrototypes;
    std::vector<Agent*> m_player2AgentPrototypes;

    void setupUI();

};

#endif
