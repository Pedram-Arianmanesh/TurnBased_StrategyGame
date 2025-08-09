#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "cell.h"
#include "agent.h"
#include <vector>

using Board = std::vector<std::vector<Cell>>;

class GameBoard
{
public:
    GameBoard(const Board& parsedBoard);

    Cell* getCell(int row, int col);
    int getRows() const { return m_cells.size(); }
    int getCols(int row) const { return m_cells[row].size(); }

    void placeAgent(Agent* agent, int row, int col);
    void removeAgent(int row, int col);
    void moveAgent(Agent* agent, int fromRow, int fromCol, int toRow, int toCol);
    void clearStartZones();

    void resetBfsState();
    std::vector<Cell*> getReachableCells(Cell* startCell, int mobility, int playerOwner);

    int countAgents(int playerOwner) const;

protected:
    void setupNeighbors();

private:
    Board m_cells;
};

#endif
