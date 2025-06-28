#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "cell.h"
#include "agent.h"
#include <vector>
#include <QPoint>

using Board = std::vector<std::vector<Cell>>;

class GameBoard {
public:
    GameBoard(const Board& parsedBoard);

    void setupNeighbors();

    Cell* getCell(int row, int col);

    void placeAgent(Agent* agent, int row, int col);
    void removeAgent(int row, int col);
    void moveAgent(Agent* agent, int fromRow, int fromCol, int toRow, int toCol);

    void resetBfsState();

    int getRows() const { return m_cells.size(); }
    int getCols(int row) const { return (row >= 0 && row < m_cells.size()) ? m_cells[row].size() : 0; }

    const Board& getCellsRef() const { return m_cells; }


private:
    Board m_cells;
};

#endif
