#ifndef HEXBOARDWIDGET_H
#define HEXBOARDWIDGET_H

#include <QWidget>
#include <QMap>
#include "logic/gameboard.h"
#include "logic/cell.h"
#include "logic/agent.h"

class QDragEnterEvent;
class QDropEvent;

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
