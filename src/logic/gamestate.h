#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include <QVector>
#include <QString>

class GameBoard;
class Agent;

enum class GamePhase {
    Deployment,
    Combat
};

class GameState : public QObject
{
    Q_OBJECT

public:
    explicit GameState(QObject *parent = nullptr);

    GamePhase getCurrentPhase() const;
    int getCurrentPlayer() const;
    int getPlayerPlacedAgents(int player) const;

public slots:
    void nextTurn();
    void agentPlaced(int player);
    void startGame();

private:
    GamePhase m_currentPhase = GamePhase::Deployment;
    int m_currentPlayer = 1;
    QVector<int> m_placedAgents;
};

#endif
