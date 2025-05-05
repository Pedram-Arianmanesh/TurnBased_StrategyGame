#include "menupage.h"
#include "playerdialog.h"
#include "gamepage.h"
#include "agentgallery.h"
#include "agent.h"
#include <QMessageBox>
#include <QPixmap>

MenuPage::MenuPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::MenuPage)
{
    ui->setupUi(this);

    connect(ui->GalleryButton, &QPushButton::clicked, this, &MenuPage::onGalleryClicked);
    connect(ui->StartPvPButton, &QPushButton::clicked, this, &MenuPage::onStartPvPClicked);
}
void MenuPage::onGalleryClicked()
{
    std::vector<Agent> agents = {
        Agent("Warrior", QPixmap(":/images/agents/warrior.png")),
        Agent("Archer",  QPixmap(":/images/agents/archer.png")),
        Agent("Mage",    QPixmap(":/images/agents/mage.png"))
    };


    AgentGallery *gallery = new AgentGallery(agents);
    gallery->show();
}


void MenuPage::onStartPvPClicked()
{
    PlayerDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        GamePage *game = new GamePage(nullptr,
                                      dialog.player1Name(),
                                      dialog.player2Name());
        game->show();
        this->close();
    }
}
