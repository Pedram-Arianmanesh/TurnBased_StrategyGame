#ifndef HEXBOARDWIDGET_H
#define HEXBOARDWIDGET_H

#include <QWidget>
#include "cell.h"
#include <vector>

using Board = std::vector<std::vector<Cell>>;

class HexBoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit HexBoardWidget(const Board &boardData, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Board m_board;
};

#endif
