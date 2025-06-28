#include "agent.h"

Agent::Agent(const QString &name, const QString &type, const QPixmap &icon, int h, int m, int d, int a)
    : m_name(name), m_type(type), m_icon(icon),
    hp(h), mobility(m), damage(d), attack_range(a) {}

QString Agent::name() const {
    return m_name;
}

QString Agent::type() const {
    return m_type;
}

QPixmap Agent::icon() const {
    return m_icon;
}

int Agent::getHp() const {
    return hp;
}

int Agent::getMobility() const {
    return mobility;
}

int Agent::getDamage() const {
    return damage;
}

int Agent::getAttackRange() const {
    return attack_range;
}

Grounded::Grounded(const QString &name, const QPixmap &icon, int h, int m, int d, int a)
    : Agent(name, "Grounded", icon, h, m, d, a){
    walk_water = false;
    walk_rock = false;
    stand_water = false;
    stand_rock = false;
}

Water_Walking::Water_Walking(const QString &name, const QPixmap &icon, int h, int m, int d, int a):
    Agent(name, "Water_Walking", icon, h, m, d, a){
    walk_water = true;
    walk_rock = false;
    stand_water = true;
    stand_rock = false;
}

Flying::Flying(const QString &name, const QPixmap &icon, int h, int m, int d, int a)
    : Agent(name, "Flying", icon, h, m, d, a){
    walk_water = true;
    walk_rock = true;
    stand_water = false;
    stand_rock = false;
}

Floating::Floating(const QString &name, const QPixmap &icon, int h, int m, int d, int a)
    : Agent(name, "Floating", icon, h, m, d, a){
    walk_water = true;
    walk_rock = true;
    stand_water = true;
    stand_rock = true;
}
