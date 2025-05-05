#include "agent.h"

Agent::Agent(const QString &name, const QPixmap &icon)
    : m_name(name), m_icon(icon) {}

QString Agent::name() const {
    return m_name;
}

QPixmap Agent::icon() const {
    return m_icon;
}
