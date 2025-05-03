#include "cell.h"

// سازنده پیش‌فرض (مقداردهی اولیه امن)
Cell::Cell()
    : row(0), col(0), terrain(TerrainType::Free), owner(0) {}

// سازنده اصلی
Cell::Cell(int r, int c, TerrainType t, int o)
    : row(r), col(c), terrain(t), owner(o) {}
