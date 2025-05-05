// gamepage.cpp
#include "gamepage.h"
#include "boardparser.h"
#include "hexboardwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QFrame>

GamePage::GamePage(QWidget *parent, const QString &player1, const QString &player2)
    : QWidget(parent), m_player1(player1), m_player2(player2)
{
    setWindowTitle("Tactical Monsters - Game");
    resize(1920, 1080);
    setupUI();
}

class AgentCard : public QLabel {
public:
    explicit AgentCard(const QString &name, const QString &imgPath, QWidget *parent = nullptr)
        : QLabel(parent), m_name(name) {
        setPixmap(QPixmap(imgPath).scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        setAlignment(Qt::AlignCenter);
        setFixedSize(110, 110);
        setStyleSheet("border: 2px solid gray; border-radius: 10px; background: white;");
        setCursor(Qt::OpenHandCursor);
    }

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(m_name);
            drag->setMimeData(mimeData);
            drag->setPixmap(pixmap());
            drag->exec();
        }
    }


private:
    QString m_name;
};

void GamePage::setupUI()
{
    qDebug() << "⏳ Loading board...";
    Board board = BoardParser::parseBoard(":/maps/grid1.txt");
    qDebug() << "✅ Loaded board rows:" << board.size();
    if (board.empty()) {
        qWarning() << "❗ Board is empty. Check your map file path!";
    }

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 1
    QVBoxLayout *leftPanel = new QVBoxLayout;
    QLabel *player1Label = new QLabel(m_player1 + " [RED]");
    player1Label->setAlignment(Qt::AlignCenter);
    player1Label->setStyleSheet("background-color: #F44336; color: white; font-weight: bold; font-size: 18px; padding: 10px; border-radius: 8px;");

    QVBoxLayout *player1Agents = new QVBoxLayout;
    QStringList redAgents = {"warrior", "archer", "mage"};
    for (const QString &name : redAgents) {
        AgentCard *card = new AgentCard(name, ":/images/agents/" + name + ".png");
        player1Agents->addWidget(card);
    }

    QFrame *leftFrame = new QFrame;
    leftFrame->setStyleSheet("background-color: #FFEBEE; border-radius: 12px;");
    leftFrame->setLayout(player1Agents);
    leftFrame->setMinimumWidth(200);

    leftPanel->addWidget(player1Label);
    leftPanel->addWidget(leftFrame);
    leftPanel->addStretch();

    // board
    HexBoardWidget *boardWidget = new HexBoardWidget(board);
    boardWidget->setAcceptDrops(true);

    // 2
    QVBoxLayout *rightPanel = new QVBoxLayout;
    QLabel *player2Label = new QLabel(m_player2 + " [BLUE]");
    player2Label->setAlignment(Qt::AlignCenter);
    player2Label->setStyleSheet("background-color: #2196F3; color: white; font-weight: bold; font-size: 18px; padding: 10px; border-radius: 8px;");

    QVBoxLayout *player2Agents = new QVBoxLayout;
    QStringList blueAgents = {"warrior", "archer", "mage"};
    for (const QString &name : blueAgents) {
        AgentCard *card = new AgentCard(name, ":/images/agents/" + name + ".png");
        player2Agents->addWidget(card);
    }


    QFrame *rightFrame = new QFrame;
    rightFrame->setStyleSheet("background-color: #E3F2FD; border-radius: 12px;");
    rightFrame->setLayout(player2Agents);
    rightFrame->setMinimumWidth(200);

    rightPanel->addWidget(player2Label);
    rightPanel->addWidget(rightFrame);
    rightPanel->addStretch();

    mainLayout->addLayout(leftPanel, 2);
    mainLayout->addWidget(boardWidget, 6);
    mainLayout->addLayout(rightPanel, 2);

    setLayout(mainLayout);
}
