
#include "boardparser.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

struct CellPattern {
    int row;
    int col;
    int line;
    int index;
};

static const std::vector<CellPattern> cellPatterns = {
    {0, 0, 1,  1}, {0, 1, 1,  6}, {0, 2, 1, 11}, {0, 3, 1, 16}, {0, 4, 1, 21},
    {1, 0, 2,  4}, {1, 1, 2,  9}, {1, 2, 2, 14}, {1, 3, 2, 19},
    {2, 0, 3,  1}, {2, 1, 3,  6}, {2, 2, 3, 11}, {2, 3, 3, 16}, {2, 4, 3, 21},
    {3, 0, 4,  4}, {3, 1, 4,  9}, {3, 2, 4, 14}, {3, 3, 4, 19},
    {4, 0, 5,  1}, {4, 1, 5,  6}, {4, 2, 5, 11}, {4, 3, 5, 16}, {4, 4, 5, 21},
    {5, 0, 6,  4}, {5, 1, 6,  9}, {5, 2, 6, 14}, {5, 3, 6, 19},
    {6, 0, 7,  1}, {6, 1, 7,  6}, {6, 2, 7, 11}, {6, 3, 7, 16}, {6, 4, 7, 21},
    {7, 0, 8,  4}, {7, 1, 8,  9}, {7, 2, 8, 14}, {7, 3, 8, 19},
    {8, 0, 9,  1}, {8, 1, 9,  6}, {8, 2, 9, 11}, {8, 3, 9, 16}, {8, 4, 9, 21}
};
Board BoardParser::parseBoard(const QString &filePath) {
    QFile file(filePath);
    Board board(9);

    for (int i = 0; i < 9; ++i)
        board[i].reserve(5);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ Cannot open map file:" << filePath;
        return board;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.trimmed().isEmpty())
            lines.append(line);
    }
    file.close();

    for (const auto &pattern : cellPatterns) {
        if (pattern.line >= lines.size()) continue;
        const QString &line = lines[pattern.line];

        TerrainType terrain = TerrainType::Free;
        int owner = 0;

        static const std::vector<int> offsets = {-1, 0, 1};
        for (int di : offsets) {
            int l = pattern.line + di;
            if (l < 0 || l >= lines.size()) continue;

            for (int dj : offsets) {
                int c = pattern.index + dj;
                if (c < 0 || c >= lines[l].size()) continue;

                QChar ch = lines[l][c];
                if (ch == '#') terrain = TerrainType::Rock;
                else if (ch == '~') terrain = TerrainType::Water;
                else if (ch == '1') owner = 1;
                else if (ch == '2') owner = 2;
            }
        }

        board[pattern.row].emplace_back(pattern.row, pattern.col, terrain, owner);
    }

    return board;
}

