#ifndef HEXBOARDWIDGET_H
#define HEXBOARDWIDGET_H

#include <QWidget>
#include <QPointF>
#include <vector>
#include <functional>

class GameBoard;
class GameState;
class Cell;
class Agent;

class HexBoardWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPointF animPos READ animPos WRITE setAnimPos)

public:
    explicit HexBoardWidget(GameBoard* gameBoard, QWidget *parent = nullptr);
    void setGameState(GameState* gameState);
    void updateBoardDisplay();
    Agent* createAgentInstance(const QString& agentTypeName, int playerOwner);

signals:
    void agentPlacedOnBoard(const QString& agentTypeName, int playerOwner);
    void turnFinished();

protected:
    void paintEvent(QPaintEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    GameBoard* m_gameBoard;
    GameState* m_gameState;

    Cell* m_selectedCell = nullptr;
    std::vector<Cell*> m_reachableCells;
    std::vector<Cell*> m_attackableCells;

    QPointF m_animPos;
    bool m_isAnimating = false;
    Agent* m_animAgent = nullptr;

    QPointF animPos() const;
    void setAnimPos(const QPointF& pos);

    void animateAgentMove(Agent* agent, const QPointF& start, const QPointF& end, std::function<void()> onFinished = {});
    void animateAttack(Agent* attacker, const QPointF& start, const QPointF& target, std::function<void()> onFinished = {});

    std::pair<int,int> pointToCell(const QPointF &pt) const;
    void handleAgentMove(Cell* fromCell, Cell* toCell);
    std::vector<Cell*> getAttackableCells(Cell* startCell);
    void attackAgent(Cell* attackerCell, Cell* defenderCell);

    QPointF cellCenter(Cell* cell) const;
};

#endif
