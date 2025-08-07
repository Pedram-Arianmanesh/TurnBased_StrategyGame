#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QString>
#include <QList>
#include <vector>

class GameBoard;
class HexBoardWidget;
class GameState;
class Agent;
class AgentCard;
class QLabel;
class QVBoxLayout;

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr, const QString &player1 = "", const QString &player2 = "");
    ~GamePage();

private slots:
    void handleAgentPlaced(const QString& agentTypeName, int playerOwner);
    void handleTurnFinished();

private:
    void setupUI();
    void updatePlayerLabels();
    void updateBoardDisplay();

    QString m_player1;
    QString m_player2;
    GameBoard* m_gameBoard;
    HexBoardWidget* m_boardWidget;
    GameState* m_gameState;

    QLabel* m_player1Label;
    QLabel* m_player2Label;
    QVBoxLayout* m_player1AgentsLayout;
    QVBoxLayout* m_player2AgentsLayout;

    std::vector<Agent*> m_player1AgentPrototypes;
    std::vector<Agent*> m_player2AgentPrototypes;
    QList<AgentCard*> m_player1AgentCards;
    QList<AgentCard*> m_player2AgentCards;
};

#endif
