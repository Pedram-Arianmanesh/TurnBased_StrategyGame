#include "gamestate.h"
#include <QDebug>

GameState::GameState(QObject *parent)
    : QObject(parent)
{
    m_placedAgents.resize(2, 0);
    qDebug() << "GameState initialized.";
}

GamePhase GameState::getCurrentPhase() const
{
    return m_currentPhase;
}

int GameState::getCurrentPlayer() const
{
    return m_currentPlayer;
}

int GameState::getPlayerPlacedAgents(int player) const
{
    if (player == 1) return m_placedAgents[0];
    if (player == 2) return m_placedAgents[1];
    return 0;
}

void GameState::nextTurn()
{
    m_currentPlayer = (m_currentPlayer == 1) ? 2 : 1;
    qDebug() << "Next turn. Current player is now:" << m_currentPlayer;
}

void GameState::agentPlaced(int player)
{
    if (player == 1) {
        m_placedAgents[0]++;
    } else if (player == 2) {
        m_placedAgents[1]++;
    }
    qDebug() << "Agent placed by Player" << player << ". Total placed for this player:" << m_placedAgents[player - 1];

    if (m_placedAgents[0] >= 5 && m_placedAgents[1] >= 5) {
        startGame();
    } else {
        nextTurn();
    }
}

void GameState::startGame()
{
    m_currentPhase = GamePhase::Combat;
    qDebug() << "Deployment phase finished. Starting Combat phase.";
}
