#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QString>
#include <vector>
#include <QList>
class GameBoard;
class HexBoardWidget;
class Agent;
class AgentCard;
class QVBoxLayout;
class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr, const QString &player1 = "Player 1", const QString &player2 = "Player 2");
    ~GamePage();

private slots:
    void handleAgentPlaced(const QString& agentTypeName, int playerOwner);

private:
    void setupUI();

    QString m_player1;
    QString m_player2;

    GameBoard* m_gameBoard;
    HexBoardWidget* m_boardWidget;

    QVBoxLayout* m_player1AgentsLayout = nullptr;
    QVBoxLayout* m_player2AgentsLayout = nullptr;

    QList<AgentCard*> m_player1AgentCards;
    QList<AgentCard*> m_player2AgentCards;

    std::vector<Agent*> m_player1AgentPrototypes;
    std::vector<Agent*> m_player2AgentPrototypes;
};

#endif
