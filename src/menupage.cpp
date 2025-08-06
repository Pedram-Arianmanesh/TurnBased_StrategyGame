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
        // Water Walking
        Agent("Billy", "Water_Walking", QPixmap(":/images/agents/Billy.png"), 320, 3, 90, 1, 0),
        Agent("Reketon", "Water_Walking", QPixmap(":/images/agents/Reketon.png"), 320, 2, 80, 2, 0),
        Agent("Angus", "Water_Walking", QPixmap(":/images/agents/Angus.png"), 400, 2, 100, 1, 0),
        Agent("Duraham", "Water_Walking", QPixmap(":/images/agents/Duraham.png"), 320, 2, 100, 2, 0),
        Agent("Colonel_Baba", "Water_Walking", QPixmap(":/images/agents/Colonel_Baba.png"), 400, 2, 100, 1, 0),
        Agent("Medusa", "Water_Walking", QPixmap(":/images/agents/Medusa.png"), 320, 2, 90, 2, 0),
        Agent("Bunka", "Water_Walking", QPixmap(":/images/agents/Bunka.png"), 320, 3, 100, 1, 0),
        Agent("Sanka", "Water_Walking", QPixmap(":/images/agents/Sanka.png"), 320, 3, 100, 1, 0),

        // Grounded
        Agent("Sir_Lamorak", "Grounded", QPixmap(":/images/agents/Sir_Lamorak.png"), 320, 3, 110, 1, 0),
        Agent("Kabu", "Grounded", QPixmap(":/images/agents/Kabu.png"), 400, 2, 120, 1, 0),
        Agent("Rajakal", "Grounded", QPixmap(":/images/agents/Rajakal.png"), 320, 2, 130, 1, 0),
        Agent("Salih", "Grounded", QPixmap(":/images/agents/Salih.png"), 400, 2, 80, 1, 0),
        Agent("Khan", "Grounded", QPixmap(":/images/agents/Khan.png"), 320, 2, 90, 1, 0),
        Agent("Boi", "Grounded", QPixmap(":/images/agents/Boi.png"), 400, 2, 100, 1, 0),
        Agent("Eloi", "Grounded", QPixmap(":/images/agents/Eloi.png"), 240, 2, 100, 2, 0),
        Agent("Kanar", "Grounded", QPixmap(":/images/agents/Kanar.png"), 160, 2, 100, 2, 0),
        Agent("Elsa", "Grounded", QPixmap(":/images/agents/Elsa.png"), 320, 2, 140, 2, 0),
        Agent("Karissa", "Grounded", QPixmap(":/images/agents/Karissa.png"), 280, 2, 80, 2, 0),
        Agent("Sir_Philip", "Grounded", QPixmap(":/images/agents/Sir_Philip.png"), 400, 2, 100, 1, 0),
        Agent("Frost", "Grounded", QPixmap(":/images/agents/Frost.png"), 260, 2, 80, 2, 0),
        Agent("Tusk", "Grounded", QPixmap(":/images/agents/Tusk.png"), 400, 2, 100, 1, 0),

        // Flying
        Agent("Rambu", "Flying", QPixmap(":/images/agents/Rambu.png"), 320, 3, 120, 1, 0),

        // Floating
        Agent("Sabrina", "Floating", QPixmap(":/images/agents/Sabrina.png"), 320, 3, 100, 1, 0),
        Agent("Death", "Floating", QPixmap(":/images/agents/Death.png"), 240, 3, 120, 2, 0)
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
