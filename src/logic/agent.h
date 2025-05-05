#ifndef AGENT_H
#define AGENT_H

#include <QString>
#include <QPixmap>

class Agent {
public:
    Agent(const QString &name, const QPixmap &icon);

    QString name() const;
    QPixmap icon() const;

private:
    QString m_name;
    QPixmap m_icon;
};

#endif
