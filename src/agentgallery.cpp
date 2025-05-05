#include "agentgallery.h"
#include "ui_agentgallery.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>

AgentGallery::AgentGallery(const std::vector<Agent> &agents, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::AgentGallery)
{
    ui->setupUi(this);

    QGridLayout *grid = qobject_cast<QGridLayout *>(ui->scrollAreaWidgetContents->layout());

    int row = 0, col = 0;
    const int columns = 5;

    for (const Agent &agent : agents) {
        QWidget *card = new QWidget;
        card->setObjectName("AgentCard");
        QVBoxLayout *vbox = new QVBoxLayout(card);

        QLabel *img = new QLabel;
        img->setPixmap(agent.icon().scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        img->setAlignment(Qt::AlignCenter);

        QLabel *name = new QLabel(agent.name());
        name->setAlignment(Qt::AlignCenter);

        vbox->addWidget(img);
        vbox->addWidget(name);
        card->setLayout(vbox);

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
