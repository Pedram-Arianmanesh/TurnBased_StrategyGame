#ifndef HEXBOARDWIDGET_H
#define HEXBOARDWIDGET_H

#include "cell.h"
#include "boardparser.h"
#include <QWidget>
#include <QMap>
#include <QString>
#include <QPair>
#include <map>

class HexBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HexBoardWidget(const Board &boardData, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Board m_board;
    std::map<std::pair<int, int>, QString> m_agentsOnBoard;

    std::pair<int, int> pointToCell(const QPointF &pt) const;
};

#endif
