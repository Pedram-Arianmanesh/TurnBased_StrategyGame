#ifndef BOARDPARSER_H
#define BOARDPARSER_H

#include "cell.h"
#include <vector>
#include <QString>

using Board = std::vector<std::vector<Cell>>;

class BoardParser {
public:
    static Board parseBoard(const QString &path);
};

#endif
