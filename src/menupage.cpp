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
        Agent("Billy", "Water_Walking", QPixmap(":/images/agents/Billy.png")),
        Agent("Reketon", "Water_Walking", QPixmap(":/images/agents/Reketon.png")),
        Agent("Angus", "Water_Walking", QPixmap(":/images/agents/Angus.png")),
        Agent("Duraham", "Water_Walking", QPixmap(":/images/agents/Duraham.png")),
        Agent("Colonel_Baba", "Water_Walking", QPixmap(":/images/agents/Colonel_Baba.png")),
        Agent("Medusa", "Water_Walking", QPixmap(":/images/agents/Medusa.png")),
        Agent("Bunka", "Water_Walking", QPixmap(":/images/agents/Bunka.png")),
        Agent("Sanka", "Water_Walking", QPixmap(":/images/agents/Sanka.png")),


        Agent("Sir_Lamorak", "Grounded", QPixmap(":/images/agents/Sir_Lamorak.png")),
        Agent("Kabu", "Grounded", QPixmap(":/images/agents/Kabu.png")),
        Agent("Rajakal", "Grounded", QPixmap(":/images/agents/Rajakal.png")),
        Agent("Salih", "Grounded", QPixmap(":/images/agents/Salih.png")),
        Agent("Khan", "Grounded", QPixmap(":/images/agents/Khan.png")),
        Agent("Boi", "Grounded", QPixmap(":/images/agents/Boi.png")),
        Agent("Eloi", "Grounded", QPixmap(":/images/agents/Eloi.png")),
        Agent("Kanar", "Grounded", QPixmap(":/images/agents/Kanar.png")),
        Agent("Elsa", "Grounded", QPixmap(":/images/agents/Elsa.png")),
        Agent("Karissa", "Grounded", QPixmap(":/images/agents/Karissa.png")),
        Agent("Sir_Philip", "Grounded", QPixmap(":/images/agents/Sir_Philip.png")),
        Agent("Frost", "Grounded", QPixmap(":/images/agents/Frost.png")),
        Agent("Tusk", "Grounded", QPixmap(":/images/agents/Tusk.png")),


        Agent("Rambu", "Flying", QPixmap(":/images/agents/Rambu.png")),


        Agent("Sabrina", "Floating", QPixmap(":/images/agents/Sabrina.png")),
        Agent("Death", "Floating", QPixmap(":/images/agents/Death.png"))
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
