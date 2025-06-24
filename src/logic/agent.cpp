#include "agent.h"

Agent::Agent(const QString &name, const QString &type, const QPixmap &icon, int h, int m, int d, int a)
    : m_name(name), m_type(type), m_icon(icon)
    , hp(h), mobility(m), damage(d), attack_range(a){}

QString Agent::name() const {
    return m_name;
}

QString Agent::type() const {
    return m_type;
}

QPixmap Agent::icon() const {
    return m_icon;
}


Grounded::Grounded(const QString &name, const QPixmap &icon, int h, int m, int d, int a)
    : Agent(name, "Grounded", icon, h, m, d, a){
    walk_water = 0;
    walk_rock = 0;
    stand_water = 0;
    stand_rock = 0;
}


Water_Walking::Water_Walking(const QString &name, const QPixmap &icon, int h, int m, int d, int a):
    Agent(name, "Water_Walking", icon, h, m, d, a){
    walk_water = 1;
    walk_rock = 0;
    stand_water = 1;
    stand_rock = 0;
}


Flying::Flying(const QString &name, const QPixmap &icon, int h, int m, int d, int a)
    : Agent(name, "Flying", icon, h, m, d, a){
    walk_water = 1;
    walk_rock = 1;
    stand_water = 0;
    stand_rock = 0;
}


Floating::Floating(const QString &name, const QPixmap &icon, int h, int m, int d, int a)
    : Agent(name, "Floating", icon, h, m, d, a){
    walk_water = 1;
    walk_rock = 1;
    stand_water = 1;
    stand_rock = 1;
}
