#include "gamepage.h"
#include "boardparser.h"
#include "agentcard.h"
#include "hexboardwidget.h"
#include "logic/gameboard.h"
#include "logic/gamestate.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QFrame>
#include <QLayoutItem>
#include <QDataStream>
#include <QScrollArea>
#include <cstdlib>
#include <ctime>
#include "logic/agent.h"

GamePage::GamePage(QWidget *parent, const QString &player1, const QString &player2)
    : QWidget(parent), m_player1(player1), m_player2(player2),
    m_gameBoard(nullptr), m_boardWidget(nullptr), m_gameState(nullptr)
{
    setWindowTitle("Tactical Monsters - Game");
    resize(1920, 1080);
    setupUI();
    qDebug() << "GamePage initialized for players:" << m_player1 << "and" << m_player2;
}

GamePage::~GamePage()
{
    qDebug() << "GamePage destructor called.";
    delete m_boardWidget;
    delete m_gameBoard;
    delete m_gameState;

    for (Agent* agentPrototype : m_player1AgentPrototypes) {
        qDebug() << "Deleting Player 1 agent prototype:" << (agentPrototype ? agentPrototype->name() : "NULL Prototype");
        delete agentPrototype;
    }
    for (Agent* agentPrototype : m_player2AgentPrototypes) {
        qDebug() << "Deleting Player 2 agent prototype:" << (agentPrototype ? agentPrototype->name() : "NULL Prototype");
        delete agentPrototype;
    }
    m_player1AgentPrototypes.clear();
    m_player2AgentPrototypes.clear();

    m_player1AgentCards.clear();
    m_player2AgentCards.clear();

    qDebug() << "All resources for GamePage cleaned up.";
}


void GamePage::setupUI()
{
    QString filePath;
    std::srand(std::time(nullptr));
    int randomNumber = std::rand() % 8 + 1;
    switch (randomNumber) {
    case 1: filePath = ":/maps/grid1.txt"; break;
    case 2: filePath = ":/maps/grid2.txt"; break;
    case 3: filePath = ":/maps/grid3.txt"; break;
    case 4: filePath = ":/maps/grid4.txt"; break;
    case 5: filePath = ":/maps/grid5.txt"; break;
    case 6: filePath = ":/maps/grid6.txt"; break;
    case 7: filePath = ":/maps/grid7.txt"; break;
    case 8: filePath = ":/maps/grid8.txt"; break;
    }

    qDebug() << "GamePage: setupUI started.";
    Board boardData = BoardParser::parseBoard(filePath);
    qDebug() << "GamePage: Board parsed. Rows:" << boardData.size();
    if (boardData.empty()) {
        qWarning() << "❗ Board is empty. Check your map file path!";
        return;
    }

    m_gameBoard = new GameBoard(boardData);
    qDebug() << "GamePage: GameBoard created and neighbors set up.";
    m_gameState = new GameState(this);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    std::vector<Agent*> allAgentPrototypes;
    // Water Walking
    allAgentPrototypes.push_back(new Water_Walking("Billy", QPixmap(":/images/agents/Billy.png"), 320, 3, 90, 1, 0));
    allAgentPrototypes.push_back(new Water_Walking("Reketon", QPixmap(":/images/agents/Reketon.png"), 320, 2, 80, 2, 0));
    allAgentPrototypes.push_back(new Water_Walking("Angus", QPixmap(":/images/agents/Angus.png"), 400, 2, 100, 1, 0));
    allAgentPrototypes.push_back(new Water_Walking("Duraham", QPixmap(":/images/agents/Duraham.png"), 320, 2, 100, 2, 0));
    allAgentPrototypes.push_back(new Water_Walking("Colonel_Baba", QPixmap(":/images/agents/Colonel_Baba.png"), 400, 2, 100, 1, 0));
    allAgentPrototypes.push_back(new Water_Walking("Medusa", QPixmap(":/images/agents/Medusa.png"), 320, 2, 90, 2, 0));
    allAgentPrototypes.push_back(new Water_Walking("Bunka", QPixmap(":/images/agents/Bunka.png"), 320, 3, 100, 1, 0));
    allAgentPrototypes.push_back(new Water_Walking("Sanka", QPixmap(":/images/agents/Sanka.png"), 320, 3, 100, 1, 0));

    // Grounded
    allAgentPrototypes.push_back(new Grounded("Sir_Lamorak", QPixmap(":/images/agents/Sir_Lamorak.png"), 320, 3, 110, 1, 0));
    allAgentPrototypes.push_back(new Grounded("Kabu", QPixmap(":/images/agents/Kabu.png"), 400, 2, 120, 1, 0));
    allAgentPrototypes.push_back(new Grounded("Rajakal", QPixmap(":/images/agents/Rajakal.png"), 320, 2, 130, 1, 0));
    allAgentPrototypes.push_back(new Grounded("Salih", QPixmap(":/images/agents/Salih.png"), 400, 2, 80, 1, 0));
    allAgentPrototypes.push_back(new Grounded("Khan", QPixmap(":/images/agents/Khan.png"), 320, 2, 90, 1, 0));
    allAgentPrototypes.push_back(new Grounded("Boi", QPixmap(":/images/agents/Boi.png"), 400, 2, 100, 1, 0));
    allAgentPrototypes.push_back(new Grounded("Eloi", QPixmap(":/images/agents/Eloi.png"), 240, 2, 100, 2, 0));
    allAgentPrototypes.push_back(new Grounded("Kanar", QPixmap(":/images/agents/Kanar.png"), 160, 2, 100, 2, 0));
    allAgentPrototypes.push_back(new Grounded("Elsa", QPixmap(":/images/agents/Elsa.png"), 320, 2, 140, 2, 0));
    allAgentPrototypes.push_back(new Grounded("Karissa", QPixmap(":/images/agents/Karissa.png"), 280, 2, 80, 2, 0));
    allAgentPrototypes.push_back(new Grounded("Sir_Philip", QPixmap(":/images/agents/Sir_Philip.png"), 400, 2, 100, 1, 0));
    allAgentPrototypes.push_back(new Grounded("Frost", QPixmap(":/images/agents/Frost.png"), 260, 2, 80, 2, 0));
    allAgentPrototypes.push_back(new Grounded("Tusk", QPixmap(":/images/agents/Tusk.png"), 400, 2, 100, 1, 0));

    // Flying
    allAgentPrototypes.push_back(new Flying("Rambu", QPixmap(":/images/agents/Rambu.png"), 320, 3, 120, 1, 0));

    // Floating
    allAgentPrototypes.push_back(new Floating("Sabrina", QPixmap(":/images/agents/Sabrina.png"), 320, 3, 100, 1, 0));
    allAgentPrototypes.push_back(new Floating("Death", QPixmap(":/images/agents/Death.png"), 240, 3, 120, 2, 0));

    // Left Panel for Player 1
    QVBoxLayout *leftPanel = new QVBoxLayout(this);
    m_player1Label = new QLabel(m_player1);
    m_player1Label->setAlignment(Qt::AlignCenter);
    m_player1Label->setStyleSheet("background-color: #F44336; color: white; font-weight: bold; font-size: 18px; padding: 10px; border-radius: 8px;");

    m_player1AgentsLayout = new QVBoxLayout;
    m_player1AgentsLayout->setAlignment(Qt::AlignHCenter);
    m_player1AgentsLayout->addStretch();
    m_player1AgentPrototypes = allAgentPrototypes;
    qDebug() << "GamePage: Player 1 agent prototypes count:" << m_player1AgentPrototypes.size();
    for (Agent* agentPrototype : m_player1AgentPrototypes) {
        AgentCard *card = new AgentCard(agentPrototype, 1);
        m_player1AgentsLayout->addWidget(card);
        m_player1AgentCards.append(card);
        qDebug() << "GamePage: Added AgentCard for Player 1 prototype: " << (agentPrototype ? agentPrototype->name() : "NULL") << " at " << (void*)agentPrototype;
    }
    m_player1AgentsLayout->addStretch();

    QFrame *leftFrame = new QFrame;
    leftFrame->setObjectName("leftFrame");
    leftFrame->setStyleSheet("background-color: #FFEBEE; border-radius: 12px;");
    leftFrame->setLayout(m_player1AgentsLayout);

    QScrollArea *leftScrollArea = new QScrollArea;
    leftScrollArea->setWidgetResizable(true);
    leftScrollArea->setWidget(leftFrame);
    leftScrollArea->setMinimumWidth(280);
    leftScrollArea->setMaximumWidth(320);
    leftScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    leftPanel->addWidget(m_player1Label);
    leftPanel->addWidget(leftScrollArea);


    // HexBoardWidget (Board)
    m_boardWidget = new HexBoardWidget(m_gameBoard, this);
    m_boardWidget->setAcceptDrops(true);
    connect(m_boardWidget, &HexBoardWidget::agentPlacedOnBoard, this, &GamePage::handleAgentPlaced);
    connect(m_boardWidget, &HexBoardWidget::moveAgentRequested, this, &GamePage::handleMoveAgentRequested);
    m_boardWidget->setGameState(m_gameState);
    qDebug() << "GamePage: HexBoardWidget::agentPlacedOnBoard signal is NOW connected for card removal.";

    // Right Panel for Player 2
    QVBoxLayout *rightPanel = new QVBoxLayout(this);
    m_player2Label = new QLabel(m_player2);
    m_player2Label->setAlignment(Qt::AlignCenter);
    m_player2Label->setStyleSheet("background-color: #2196F3; color: white; font-weight: bold; font-size: 18px; padding: 10px; border-radius: 8px;");

    m_player2AgentsLayout = new QVBoxLayout;
    m_player2AgentsLayout->setAlignment(Qt::AlignHCenter);
    m_player2AgentsLayout->addStretch();
    m_player2AgentPrototypes = allAgentPrototypes;
    qDebug() << "GamePage: Player 2 agent prototypes count:" << m_player2AgentPrototypes.size();
    for (Agent* agentPrototype : m_player2AgentPrototypes) {
        AgentCard *card = new AgentCard(agentPrototype, 2);
        m_player2AgentsLayout->addWidget(card);
        m_player2AgentCards.append(card);
        qDebug() << "GamePage: Added AgentCard for Player 2 prototype: " << (agentPrototype ? agentPrototype->name() : "NULL") << " at " << (void*)agentPrototype;
    }
    m_player2AgentsLayout->addStretch();

    QFrame *rightFrame = new QFrame;
    rightFrame->setObjectName("rightFrame");
    rightFrame->setStyleSheet("background-color: #E3F2FD; border-radius: 12px;");
    rightFrame->setLayout(m_player2AgentsLayout);

    QScrollArea *rightScrollArea = new QScrollArea;
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setWidget(rightFrame);
    rightScrollArea->setMinimumWidth(280);
    rightScrollArea->setMaximumWidth(320);
    rightScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    rightPanel->addWidget(m_player2Label);
    rightPanel->addWidget(rightScrollArea);

    mainLayout->addLayout(leftPanel, 3);
    mainLayout->addWidget(m_boardWidget, 4);
    mainLayout->addLayout(rightPanel, 3);

    setLayout(mainLayout);
    updatePlayerLabels();
    qDebug() << "GamePage: setupUI finished.";
}

void GamePage::handleAgentPlaced(const QString& agentTypeName, int playerOwner) {
    if (m_gameState->getCurrentPhase() != GamePhase::Deployment) {
        qWarning() << "Attempted to place agent outside of deployment phase!";
        return;
    }

    if (m_gameState->getCurrentPlayer() != playerOwner) {
        qWarning() << "It's not player" << playerOwner << "'s turn to place an agent.";
        return;
    }

    qDebug() << "GamePage: Received agentPlacedOnBoard signal for agent:" << agentTypeName << " by player:" << playerOwner;

    QList<AgentCard*>* targetList = nullptr;
    QVBoxLayout* targetLayout = nullptr;

    if (playerOwner == 1) {
        targetList = &m_player1AgentCards;
        targetLayout = m_player1AgentsLayout;
    } else if (playerOwner == 2) {
        targetList = &m_player2AgentCards;
        targetLayout = m_player2AgentsLayout;
    }

    if (targetList && targetLayout) {
        AgentCard* cardToRemove = nullptr;
        for (AgentCard* card : *targetList) {
            if (card->getAgentPrototype()->name() == agentTypeName) {
                cardToRemove = card;
                break;
            }
        }

        if (cardToRemove) {
            targetLayout->removeWidget(cardToRemove);
            cardToRemove->deleteLater();

            targetList->removeOne(cardToRemove);
            qDebug() << "GamePage: AgentCard for" << agentTypeName << "removed successfully for player" << playerOwner;

            m_gameState->agentPlaced(playerOwner);
            updatePlayerLabels();

            if (m_gameState->getCurrentPhase() == GamePhase::Combat) {
                m_gameBoard->clearStartZones();
                updateBoardDisplay();
            }
        } else {
            qWarning() << "GamePage: Could not find AgentCard for agent:" << agentTypeName << " in player" << playerOwner << " list.";
        }
    } else {
        qWarning() << "GamePage: Target list or layout not found for player" << playerOwner;
    }
}

void GamePage::updatePlayerLabels() {
    QString phaseText = m_gameState->getCurrentPhase() == GamePhase::Deployment ? " (Deployment)" : " (Combat)";
    QString turnText = QString(" - Turn: %1").arg(m_gameState->getCurrentPlayer() == 1 ? m_player1 : m_player2);
    QString player1Text = QString("%1 (%2/5)").arg(m_player1).arg(m_gameState->getPlayerPlacedAgents(1));
    QString player2Text = QString("%1 (%2/5)").arg(m_player2).arg(m_gameState->getPlayerPlacedAgents(2));

    m_player1Label->setText(player1Text + (m_gameState->getCurrentPlayer() == 1 ? phaseText + turnText : ""));
    m_player2Label->setText(player2Text + (m_gameState->getCurrentPlayer() == 2 ? phaseText + turnText : ""));

    m_player1Label->setStyleSheet(m_gameState->getCurrentPlayer() == 1 ? "border: 3px solid white; border-radius: 8px; background-color: #F44336; color: white; font-weight: bold; font-size: 18px; padding: 10px;" : "border: 3px solid transparent; border-radius: 8px; background-color: #F44336; color: white; font-weight: bold; font-size: 18px; padding: 10px;");
    m_player2Label->setStyleSheet(m_gameState->getCurrentPlayer() == 2 ? "border: 3px solid white; border-radius: 8px; background-color: #2196F3; color: white; font-weight: bold; font-size: 18px; padding: 10px;" : "border: 3px solid transparent; border-radius: 8px; background-color: #2196F3; color: white; font-weight: bold; font-size: 18px; padding: 10px;");
}

void GamePage::updateBoardDisplay() {
    if (m_boardWidget) {
        m_boardWidget->update();
    }
}

void GamePage::handleMoveAgentRequested(int fromRow, int fromCol, int toRow, int toCol) {
    if (m_gameState->getCurrentPhase() != GamePhase::Combat) {
        qWarning() << "Cannot move agents outside of combat phase!";
        return;
    }

    Cell* fromCell = m_gameBoard->getCell(fromRow, fromCol);
    if (!fromCell || !fromCell->occupiedAgent) {
        qWarning() << "Invalid move request: no agent at start cell.";
        return;
    }

    if (fromCell->occupiedAgent->getOwner() != m_gameState->getCurrentPlayer()) {
        qWarning() << "It's not your turn to move this agent.";
        return;
    }

    m_gameBoard->moveAgent(fromCell->occupiedAgent, fromRow, fromCol, toRow, toCol);
    m_gameState->nextTurn();
    updateBoardDisplay();
    updatePlayerLabels();
}
