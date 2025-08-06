#include "gameboard.h"
#include <QDebug>
#include <QQueue>

GameBoard::GameBoard(const Board& parsedBoard)
    : m_cells(parsedBoard)
{
    setupNeighbors();
}

void GameBoard::setupNeighbors() {
    for (size_t r = 0; r < m_cells.size(); ++r) {
        for (size_t c = 0; c < m_cells[r].size(); ++c) {
            Cell* currentCell = &m_cells[r][c];
            currentCell->neighbors.clear();

            if (getCell(r - 1, c)) currentCell->neighbors.push_back(getCell(r - 1, c));
            if (getCell(r + 1, c)) currentCell->neighbors.push_back(getCell(r + 1, c));

            if (r % 2 == 0) {
                if (getCell(r, c - 1)) currentCell->neighbors.push_back(getCell(r, c - 1));
                if (getCell(r, c + 1)) currentCell->neighbors.push_back(getCell(r, c + 1));
                if (getCell(r - 1, c - 1)) currentCell->neighbors.push_back(getCell(r - 1, c - 1));
                if (getCell(r + 1, c - 1)) currentCell->neighbors.push_back(getCell(r + 1, c - 1));
            } else {
                if (getCell(r, c - 1)) currentCell->neighbors.push_back(getCell(r, c - 1));
                if (getCell(r, c + 1)) currentCell->neighbors.push_back(getCell(r, c + 1));
                if (getCell(r - 1, c + 1)) currentCell->neighbors.push_back(getCell(r - 1, c + 1));
                if (getCell(r + 1, c + 1)) currentCell->neighbors.push_back(getCell(r + 1, c + 1));
            }
        }
    }
}



Cell* GameBoard::getCell(int row, int col) {
    if (row >= 0 && (size_t)row < m_cells.size()) {
        if (col >= 0 && (size_t)col < m_cells[row].size()) {
            return &m_cells[row][col];
        }
    }
    return nullptr;
}

void GameBoard::placeAgent(Agent* agent, int row, int col) {
    Cell* cell = getCell(row, col);
    if (cell) {
        if (cell->occupiedAgent) {
            qWarning() << "تلاش برای قرار دادن ایجنت روی سلول از قبل اشغال شده در (" << row << "," << col << ")";
            return;
        }
        cell->occupiedAgent = agent;
    } else {
        qWarning() << "تلاش برای قرار دادن ایجنت روی سلول نامعتبر در (" << row << "," << col << ")";
    }
}

void GameBoard::removeAgent(int row, int col) {
    Cell* cell = getCell(row, col);
    if (cell) {
        if (!cell->occupiedAgent) {
            qWarning() << "تلاش برای حذف ایجنت از سلول خالی در (" << row << "," << col << ")";
            return;
        }
        cell->occupiedAgent = nullptr;
    } else {
        qWarning() << "تلاش برای حذف ایجنت از سلول نامعتبر در (" << row << "," << col << ")";
    }
}

void GameBoard::moveAgent(Agent* agent, int fromRow, int fromCol, int toRow, int toCol) {
    Cell* fromCell = getCell(fromRow, fromCol);
    Cell* toCell = getCell(toRow, toCol);

    if (!fromCell || !toCell) {
        qWarning() << "تلاش برای جابجایی ایجنت به/از سلول نامعتبر.";
        return;
    }
    if (fromCell->occupiedAgent != agent) {
        qWarning() << "ایجنت در fromCell با ایجنت در حال جابجایی مطابقت ندارد.";
        return;
    }
    if (toCell->occupiedAgent) {
        qWarning() << "سلول مقصد در (" << toRow << "," << toCol << ") از قبل اشغال شده است.";
        return;
    }

    toCell->occupiedAgent = agent;
    fromCell->occupiedAgent = nullptr;

}

void GameBoard::clearStartZones() {
    for (size_t r = 0; r < m_cells.size(); ++r) {
        for (size_t c = 0; c < m_cells[r].size(); ++c) {
            if (m_cells[r][c].owner != 0) {
                m_cells[r][c].owner = 0;
            }
        }
    }
    qDebug() << "Start zones cleared. All cells are now Free territory.";
}

void GameBoard::resetBfsState() {
    for (size_t r = 0; r < m_cells.size(); ++r) {
        for (size_t c = 0; c < m_cells[r].size(); ++c) {
            m_cells[r][c].visited = false;
            m_cells[r][c].parent = nullptr;
            m_cells[r][c].distance = -1;
        }
    }
}

std::vector<Cell*> GameBoard::getReachableCells(Cell* startCell, int mobility, int playerOwner) {
    resetBfsState();

    std::vector<Cell*> reachableCells;
    QQueue<Cell*> q;

    startCell->distance = 0;
    startCell->visited = true;
    q.enqueue(startCell);

    while (!q.isEmpty()) {
        Cell* currentCell = q.dequeue();

        if (currentCell->distance < mobility) {
            for (Cell* neighbor : currentCell->neighbors) {

                if (!neighbor->visited && !neighbor->occupiedAgent && (neighbor->owner != playerOwner)) {
                    bool canMoveToNeighbor = false;

                    if (startCell->occupiedAgent->type() == "Grounded" && neighbor->terrain == TerrainType::Free) {
                        canMoveToNeighbor = true;
                    } else if (startCell->occupiedAgent->type() == "Water_Walking" && (neighbor->terrain == TerrainType::Free || neighbor->terrain == TerrainType::Water)) {
                        canMoveToNeighbor = true;
                    } else if (startCell->occupiedAgent->type() == "Flying" && (neighbor->terrain == TerrainType::Free || neighbor->terrain == TerrainType::Water || neighbor->terrain == TerrainType::Rock)) {
                        canMoveToNeighbor = true;
                    } else if (startCell->occupiedAgent->type() == "Floating" && (neighbor->terrain == TerrainType::Free || neighbor->terrain == TerrainType::Water || neighbor->terrain == TerrainType::Rock)) {
                        canMoveToNeighbor = true;
                    }

                    if (canMoveToNeighbor) {
                        neighbor->visited = true;
                        neighbor->distance = currentCell->distance + 1;
                        neighbor->parent = currentCell;
                        q.enqueue(neighbor);
                        reachableCells.push_back(neighbor);
                    }
                }
            }
        }
    }

    return reachableCells;
}
