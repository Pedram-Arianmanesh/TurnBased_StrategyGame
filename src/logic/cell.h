#ifndef CELL_H
#define CELL_H

enum class TerrainType {
    Free,
    Water,
    Rock
};

class Cell {
public:
    int row;
    int col;
    TerrainType terrain;
    int owner;

    Cell();

    Cell(int r, int c, TerrainType t, int o = 0);
};

#endif
