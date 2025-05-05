#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QString>

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr,
                      const QString &player1 = "Player 1",
                      const QString &player2 = "Player 2");

private:
    QString m_player1;
    QString m_player2;

    void setupUI();
};

#endif
