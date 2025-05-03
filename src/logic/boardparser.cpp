#include "boardparser.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Board BoardParser::parseBoard(const QString &filePath) {
    Board board(9);

    for (int r = 0; r < 9; ++r) {
        int cols = (r % 2 == 0) ? 5 : 4;
        for (int c = 0; c < cols; ++c) {
            board[r].emplace_back(r, c, TerrainType::Free, 0);
        }
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ Cannot open map file:" << filePath;
        return board;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        lines << line;
    }

    file.close();

    int boardRow = 0;
    for (int i = 1; i < lines.size() - 1 && boardRow < 9; ++i) {
        QString line = lines[i];
        if (line.trimmed().isEmpty()) continue;

        int expectedCols = (boardRow % 2 == 0) ? 5 : 4;
        int cellIndex = 0;

        for (int pos = 0; pos < line.length(); ++pos) {
            QChar ch = line[pos];
            if (ch == '/' || ch == '\\' || ch == '_' || ch.isSpace()) continue;

            if (cellIndex >= expectedCols) break;

            Cell &cell = board[boardRow][cellIndex];

            if (ch == '1') cell.owner = 1;
            else if (ch == '2') cell.owner = 2;
            else if (ch == '#') cell.terrain = TerrainType::Rock;
            else if (ch == '~') cell.terrain = TerrainType::Water;

            ++cellIndex;
        }

        ++boardRow;
    }

    return board;
}
