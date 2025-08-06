#ifndef AGENT_H
#define AGENT_H

#include <QString>
#include <QPixmap>

class Agent
{
public:
    Agent(const QString &name, const QString &type, const QPixmap &icon, int h, int m, int d, int a, int o);

    QString name() const;
    QString type() const;
    QPixmap icon() const;

    int getHp() const;
    int getMobility() const;
    int getDamage() const;
    int getAttackRange() const;
    int getOwner() const;

protected:
    QString m_name;
    QString m_type;
    QPixmap m_icon;
    int owner;
    int hp;
    int mobility;
    int damage;
    int attack_range;

    bool walk_water = false;
    bool walk_rock = false;
    bool stand_water = false;
    bool stand_rock = false;
};

class Grounded : public Agent
{
public:
    Grounded(const QString &name, const QPixmap &icon, int h, int m, int d, int a, int o);
};

class Water_Walking : public Agent
{
public:
    Water_Walking(const QString &name, const QPixmap &icon, int h, int m, int d, int a, int o);
};

class Flying : public Agent
{
public:
    Flying(const QString &name, const QPixmap &icon, int h, int m, int d, int a, int o);
};

class Floating : public Agent
{
public:
    Floating(const QString &name, const QPixmap &icon, int h, int m, int d, int a, int o);
};

#endif // AGENT_H
