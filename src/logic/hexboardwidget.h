#ifndef HEXBOARDWIDGET_H
#define HEXBOARDWIDGET_H

#include <QWidget>
#include <QPointF>
#include <vector>
#include <QQueue>
#include "logic/cell.h"

class GameBoard;
class GameState;
class Agent;
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
class QPaintEvent;

class HexBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HexBoardWidget(GameBoard* gameBoard, QWidget *parent = nullptr);
    void setGameState(GameState* gameState);
    void updateBoardDisplay();

protected:
    void paintEvent(QPaintEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void agentPlacedOnBoard(const QString& agentTypeName, int playerOwner);
    void turnFinished();

private:
    std::pair<int, int> pointToCell(const QPointF &pt) const;
    Agent* createAgentInstance(const QString& agentTypeName, int playerOwner);
    std::vector<Cell*> getAttackableCells(Cell* startCell);
    void attackAgent(Cell* attackerCell, Cell* defenderCell);
    void handleAgentMove(Cell* fromCell, Cell* toCell);

    GameBoard* m_gameBoard;
    GameState* m_gameState;

    Cell* m_selectedCell = nullptr;
    std::vector<Cell*> m_reachableCells;
    std::vector<Cell*> m_attackableCells;
};

#endif
