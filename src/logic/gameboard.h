#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "cell.h"
#include "agent.h"

typedef std::vector<std::vector<Cell>> Board;

class GameBoard
{
public:
    GameBoard(const Board& parsedBoard);

    void setupNeighbors();
    Cell* getCell(int row, int col);

    void placeAgent(Agent* agent, int row, int col);
    void removeAgent(int row, int col);
    void moveAgent(Agent* agent, int fromRow, int fromCol, int toRow, int toCol);
    void clearStartZones();

    void resetBfsState();

    std::vector<Cell*> getReachableCells(Cell* startCell, int mobility, int playerOwner);

    int getRows() const { return m_cells.size(); }
    int getCols(int r) const { return m_cells[r].size(); }

private:
    Board m_cells;
};

#endif
