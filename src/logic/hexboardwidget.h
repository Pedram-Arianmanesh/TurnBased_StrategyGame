#ifndef HEXBOARDWIDGET_H
#define HEXBOARDWIDGET_H

#include <QWidget>
#include <QPointF>
#include <utility>

class GameBoard;
class Cell;
class Agent;
class Water_Walking;
class Grounded;
class Flying;
class Floating;
class GameState;

class HexBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HexBoardWidget(GameBoard* gameBoard, QWidget *parent = nullptr);
    void setGameState(GameState* gameState);

signals:
    void agentPlacedOnBoard(const QString& agentTypeName, int playerOwner);
    void moveAgentRequested(int fromRow, int fromCol, int toRow, int toCol);

protected:
    void paintEvent(QPaintEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    GameBoard* m_gameBoard;
    GameState* m_gameState;
    std::pair<int, int> pointToCell(const QPointF &pt) const;
    Agent* createAgentInstance(const QString& agentTypeName, int playerOwner);
    Cell* m_selectedCell = nullptr;
    std::vector<Cell*> m_reachableCells;
};

#endif
