#include "agentcard.h"
#include <QDebug>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

AgentCard::AgentCard(Agent* agentPrototype, int playerOwner, QWidget *parent)
    : QLabel(parent), m_agentPrototype(agentPrototype), m_playerOwner(playerOwner) {
    if (m_agentPrototype) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(5, 5, 5, 5);
        mainLayout->setSpacing(5);

        QLabel *imgLabel = new QLabel;
        imgLabel->setPixmap(m_agentPrototype->icon().scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imgLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(imgLabel);

        QLabel *nameLabel = new QLabel(m_agentPrototype->name());
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setStyleSheet("font-weight: bold; font-size: 14px; margin-top: 5px; color: black;");
        mainLayout->addWidget(nameLabel);

        QHBoxLayout *statsLayout1 = new QHBoxLayout;
        statsLayout1->setContentsMargins(0,0,0,0);
        statsLayout1->setSpacing(8);
        QLabel *hpLabel = new QLabel(QString("HP: %1").arg(m_agentPrototype->getHp()));
        hpLabel->setStyleSheet("font-size: 12px; color: black;");
        QLabel *mobilityLabel = new QLabel(QString("Move: %1").arg(m_agentPrototype->getMobility()));
        mobilityLabel->setStyleSheet("font-size: 12px; color: black;");
        statsLayout1->addWidget(hpLabel);
        statsLayout1->addStretch();
        statsLayout1->addWidget(mobilityLabel);
        mainLayout->addLayout(statsLayout1);

        QHBoxLayout *statsLayout2 = new QHBoxLayout;
        statsLayout2->setContentsMargins(0,0,0,0);
        statsLayout2->setSpacing(8);
        QLabel *damageLabel = new QLabel(QString("Dmg: %1").arg(m_agentPrototype->getDamage()));
        damageLabel->setStyleSheet("font-size: 12px; color: black;");

        QString attackRangeText;
        if (m_agentPrototype->name() == "Eloi") {
            attackRangeText = "Rng: 2-3";
        } else {
            attackRangeText = QString("Rng: %1").arg(m_agentPrototype->getAttackRange());
        }
        QLabel *attackRangeLabel = new QLabel(attackRangeText);
        attackRangeLabel->setStyleSheet("font-size: 12px; color: black;");

        statsLayout2->addWidget(damageLabel);
        statsLayout2->addStretch();
        statsLayout2->addWidget(attackRangeLabel);
        mainLayout->addLayout(statsLayout2);

        setFixedSize(160, 260);
        setStyleSheet("border: 2px solid gray; border-radius: 10px; background: white;");
        setCursor(Qt::OpenHandCursor);
    }
}

Agent* AgentCard::getAgentPrototype() const {
    return m_agentPrototype;
}

int AgentCard::getPlayerOwner() const {
    return m_playerOwner;
}

void AgentCard::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && m_agentPrototype) {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        QByteArray agentData;
        QDataStream stream(&agentData, QIODevice::WriteOnly);
        stream << m_agentPrototype->name() << m_playerOwner;

        mimeData->setData("application/x-yourgame-agent-type", agentData);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap());
        drag->exec(Qt::CopyAction | Qt::MoveAction);
    }
}
