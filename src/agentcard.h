#ifndef AGENTCARD_H
#define AGENTCARD_H

#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QDataStream>
#include "logic/agent.h"

class AgentCard : public QLabel {
    Q_OBJECT

public:
    explicit AgentCard(Agent* agentPrototype, int playerOwner, QWidget *parent = nullptr);

    Agent* getAgentPrototype() const;
    int getPlayerOwner() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Agent* m_agentPrototype;
    int m_playerOwner;
};

#endif
