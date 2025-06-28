#ifndef AGENTGALLERY_H
#define AGENTGALLERY_H

#include <QWidget>
#include <vector>
#include "agent.h"

namespace Ui {
class AgentGallery;
}

class AgentGallery : public QWidget
{
    Q_OBJECT

public:
    explicit AgentGallery(const std::vector<Agent> &agents, QWidget *parent = nullptr);
    ~AgentGallery();

private:
    Ui::AgentGallery *ui;
};

#endif
