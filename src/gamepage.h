#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>

class GamePage : public QWidget {
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr,
                      const QString &player1 = "Player 1",
                      const QString &player2 = "Player 2");
};

#endif
