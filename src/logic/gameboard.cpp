#include "gameboard.h"
#include <QDebug>

GameBoard::GameBoard(const Board& parsedBoard)
    : m_cells(parsedBoard)
{
    setupNeighbors();
}

void GameBoard::setupNeighbors() {
    for (int r = 0; r < m_cells.size(); ++r) {
        for (int c = 0; c < m_cells[r].size(); ++c) {
            Cell* currentCell = &m_cells[r][c];
            currentCell->neighbors.clear();


            if (getCell(r, c + 1)) currentCell->neighbors.push_back(getCell(r, c + 1));
            if (getCell(r, c - 1)) currentCell->neighbors.push_back(getCell(r, c - 1));

            if (r % 2 == 0) {
                if (getCell(r - 1, c - 1)) currentCell->neighbors.push_back(getCell(r - 1, c - 1));
                if (getCell(r - 1, c)) currentCell->neighbors.push_back(getCell(r - 1, c));
                if (getCell(r + 1, c - 1)) currentCell->neighbors.push_back(getCell(r + 1, c - 1));
                if (getCell(r + 1, c)) currentCell->neighbors.push_back(getCell(r + 1, c));
            } else {
                if (getCell(r - 1, c)) currentCell->neighbors.push_back(getCell(r - 1, c));
                if (getCell(r - 1, c + 1)) currentCell->neighbors.push_back(getCell(r - 1, c + 1));
                if (getCell(r + 1, c)) currentCell->neighbors.push_back(getCell(r + 1, c));
                if (getCell(r + 1, c + 1)) currentCell->neighbors.push_back(getCell(r + 1, c + 1));
            }
        }
    }
}

Cell* GameBoard::getCell(int row, int col) {
    if (row >= 0 && row < m_cells.size()) {
        if (col >= 0 && col < m_cells[row].size()) {
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

void GameBoard::resetBfsState() {
    for (int r = 0; r < m_cells.size(); ++r) {
        for (int c = 0; c < m_cells[r].size(); ++c) {
            m_cells[r][c].visited = false;
            m_cells[r][c].parent = nullptr;
            m_cells[r][c].distance = -1;
        }
    }
}
