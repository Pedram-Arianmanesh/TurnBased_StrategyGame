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

class HexBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HexBoardWidget(GameBoard* gameBoard, QWidget *parent = nullptr);

signals:
    void agentPlacedOnBoard(const QString& agentTypeName, int playerOwner);

protected:
    void paintEvent(QPaintEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    GameBoard* m_gameBoard;
    std::pair<int, int> pointToCell(const QPointF &pt) const;
    Agent* createAgentInstance(const QString& agentTypeName, int playerOwner);
};

#endif
