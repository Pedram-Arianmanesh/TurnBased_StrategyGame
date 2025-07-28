#include "agentgallery.h"
#include "ui_agentgallery.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

namespace {
QLabel* createStyledLabel(const QString &text, int fontSize = 18, bool bold = false, Qt::Alignment align = Qt::AlignCenter) {
    QLabel *label = new QLabel(text);
    label->setAlignment(align);
    label->setStyleSheet(QString("font-size: %1px; color: #12fcf9; %2")
                             .arg(fontSize)
                             .arg(bold ? "font-weight: bold;" : ""));
    return label;
}
}

AgentGallery::AgentGallery(const std::vector<Agent> &agents, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::AgentGallery)
{
    ui->setupUi(this);

    QGridLayout *grid = qobject_cast<QGridLayout *>(ui->scrollAreaWidgetContents->layout());
    if (!grid) {
        grid = new QGridLayout(ui->scrollAreaWidgetContents);
        ui->scrollAreaWidgetContents->setLayout(grid);
    }

    int row = 0, col = 0;
    const int columns = 5;

    for (const Agent &agent : agents) {
        QWidget *card = new QWidget;
        card->setObjectName("AgentCard");

        QVBoxLayout *vbox = new QVBoxLayout(card);
        vbox->setContentsMargins(8, 8, 8, 8);
        vbox->setSpacing(6);

        QLabel *img = new QLabel;
        img->setPixmap(agent.icon().scaled(130, 130
                                           , Qt::KeepAspectRatio, Qt::SmoothTransformation));
        img->setAlignment(Qt::AlignCenter);

        QLabel *name = createStyledLabel(agent.name(), 20, true);
        QLabel *type = createStyledLabel(agent.type(), 16);

        vbox->addWidget(img);
        vbox->addWidget(name);
        vbox->addWidget(type);

        QHBoxLayout *statsLayout1 = new QHBoxLayout;
        statsLayout1->setContentsMargins(0, 0, 0, 0);
        statsLayout1->setSpacing(5);
        statsLayout1->addWidget(createStyledLabel(QString("HP: %1").arg(agent.getHp())));
        statsLayout1->addStretch();
        statsLayout1->addWidget(createStyledLabel(QString("Move: %1").arg(agent.getMobility())));
        vbox->addLayout(statsLayout1);

        QHBoxLayout *statsLayout2 = new QHBoxLayout;
        statsLayout2->setContentsMargins(0, 0, 0, 0);
        statsLayout2->setSpacing(5);
        statsLayout2->addWidget(createStyledLabel(QString("Dmg: %1").arg(agent.getDamage())));
        statsLayout2->addStretch();
        statsLayout2->addWidget(createStyledLabel(QString("Rng: %1").arg(agent.getAttackRange())));
        vbox->addLayout(statsLayout2);

        card->setMinimumSize(220, 290);
        card->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        card->setStyleSheet(
            "border: 2px solid #062569;"
            "border-radius: 10px;"
            "background-color: #121212;"
            );

        grid->addWidget(card, row, col);

        if (++col >= columns) {
            col = 0;
            ++row;
        }
    }
}

AgentGallery::~AgentGallery()
{
    delete ui;
}
