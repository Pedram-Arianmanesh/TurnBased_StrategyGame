#ifndef AGENT_H
#define AGENT_H

#include <QString>
#include <QPixmap>

class Agent {
public:
    Agent(const QString &name, const QString &type, const QPixmap &icon, int h = 10, int m = 1, int d = 10, int a = 1);

    QString name() const;
    QString type() const;
    QPixmap icon() const;

    int get_hp();
    int get_mobility();
    int get_damage();
    int get_attack_range();


    bool walk_water;
    bool walk_rock;
    bool stand_water;
    bool stand_rock;

private:
    QString m_name;
    QString m_type;
    QPixmap m_icon;

    int hp;
    int mobility;
    int damage;
    int attack_range;
};

class Grounded: public Agent{
public:
    Grounded(const QString &name, const QPixmap &icon, int h , int m, int d, int a);
};

class Water_Walking: public Agent{
public:
    Water_Walking(const QString &name, const QPixmap &icon, int h , int m, int d, int a);
};

class Flying: public Agent{
public:
    Flying(const QString &name, const QPixmap &icon, int h , int m, int d, int a);
};

class Floating: public Agent{
public:
    Floating(const QString &name, const QPixmap &icon, int h , int m, int d, int a);
};
#endif
