#include "hexboardwidget.h"
#include "logic/gameboard.h"
#include "logic/cell.h"
#include <QPainter>
#include <QPolygonF>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPixmap>
#include <cmath>
#include <QDebug>
#include <QDataStream>
#include "logic/agent.h"

HexBoardWidget::HexBoardWidget(GameBoard* gameBoard, QWidget *parent)
    : QWidget(parent), m_gameBoard(gameBoard)
{
    setAcceptDrops(true);
    setMinimumSize(1280, 800);
    qDebug() << "HexBoardWidget created.";
}

Agent* HexBoardWidget::createAgentInstance(const QString& agentTypeName, int playerOwner) {
    qDebug() << "createAgentInstance: Attempting to create instance for type:" << agentTypeName << "owner:" << playerOwner;

    // Water Walking
    if (agentTypeName == "Billy") { return new Water_Walking("Billy", QPixmap(":/images/agents/Billy.png"), 320, 3, 90, 1); }
    else if (agentTypeName == "Reketon") { return new Water_Walking("Reketon", QPixmap(":/images/agents/Reketon.png"), 320, 2, 80, 2); }
    else if (agentTypeName == "Angus") { return new Water_Walking("Angus", QPixmap(":/images/agents/Angus.png"), 400, 2, 100, 1); }
    else if (agentTypeName == "Duraham") { return new Water_Walking("Duraham", QPixmap(":/images/agents/Duraham.png"), 320, 2, 100, 2); }
    else if (agentTypeName == "Colonel_Baba") { return new Water_Walking("Colonel_Baba", QPixmap(":/images/agents/Colonel_Baba.png"), 400, 2, 100, 1); }
    else if (agentTypeName == "Medusa") { return new Water_Walking("Medusa", QPixmap(":/images/agents/Medusa.png"), 320, 2, 90, 2); }
    else if (agentTypeName == "Bunka") { return new Water_Walking("Bunka", QPixmap(":/images/agents/Bunka.png"), 320, 3, 100, 1); }
    else if (agentTypeName == "Sanka") { return new Water_Walking("Sanka", QPixmap(":/images/agents/Sanka.png"), 320, 3, 100, 1); }

    // Grounded
    else if (agentTypeName == "Sir_Lamorak") { return new Grounded("Sir_Lamorak", QPixmap(":/images/agents/Sir_Lamorak.png"), 320, 3, 110, 1); }
    else if (agentTypeName == "Kabu") { return new Grounded("Kabu", QPixmap(":/images/agents/Kabu.png"), 400, 2, 120, 1); }
    else if (agentTypeName == "Rajakal") { return new Grounded("Rajakal", QPixmap(":/images/agents/Rajakal.png"), 320, 2, 130, 1); }
    else if (agentTypeName == "Salih") { return new Grounded("Salih", QPixmap(":/images/agents/Salih.png"), 400, 2, 80, 1); }
    else if (agentTypeName == "Khan") { return new Grounded("Khan", QPixmap(":/images/agents/Khan.png"), 320, 2, 90, 1); }
    else if (agentTypeName == "Boi") { return new Grounded("Boi", QPixmap(":/images/agents/Boi.png"), 400, 2, 100, 1); }
    else if (agentTypeName == "Eloi") { return new Grounded("Eloi", QPixmap(":/images/agents/Eloi.png"), 240, 2, 100, 2); }
    else if (agentTypeName == "Kanar") { return new Grounded("Kanar", QPixmap(":/images/agents/Kanar.png"), 160, 2, 100, 2); }
    else if (agentTypeName == "Elsa") { return new Grounded("Elsa", QPixmap(":/images/agents/Elsa.png"), 320, 2, 140, 2); }
    else if (agentTypeName == "Karissa") { return new Grounded("Karissa", QPixmap(":/images/agents/Karissa.png"), 280, 2, 80, 2); }
    else if (agentTypeName == "Sir_Philip") { return new Grounded("Sir_Philip", QPixmap(":/images/agents/Sir_Philip.png"), 400, 2, 100, 1); }
    else if (agentTypeName == "Frost") { return new Grounded("Frost", QPixmap(":/images/agents/Frost.png"), 260, 2, 80, 2); }
    else if (agentTypeName == "Tusk") { return new Grounded("Tusk", QPixmap(":/images/agents/Tusk.png"), 400, 2, 100, 1); }

    // Flying
    else if (agentTypeName == "Rambu") { return new Flying("Rambu", QPixmap(":/images/agents/Rambu.png"), 320, 3, 120, 1); }

    // Floating
    else if (agentTypeName == "Sabrina") { return new Floating("Sabrina", QPixmap(":/images/agents/Sabrina.png"), 320, 3, 100, 1); }
    else if (agentTypeName == "Death") { return new Floating("Death", QPixmap(":/images/agents/Death.png"), 240, 3, 120, 2); }
    else {
        qWarning() << "createAgentInstance: Unknown agent type requested:" << agentTypeName;
        return nullptr;
    }
}


void HexBoardWidget::paintEvent(QPaintEvent *)
{
    if (!m_gameBoard) {
        qWarning() << "GameBoard is null in HexBoardWidget::paintEvent!";
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    double hexSize = 48.0;
    double hexWidth = 2 * hexSize;
    double hexHeight = std::sqrt(3) * hexSize;
    double horizSpacing = hexWidth * 1.5;
    double vertSpacing = hexHeight * 0.5;

    double totalRows = m_gameBoard->getRows();
    double totalCols = 5;
    double mapWidth = (totalCols - 1) * horizSpacing + hexWidth;
    double mapHeight = (totalRows - 1) * vertSpacing + hexHeight;


    double offsetX = (width() - mapWidth) / 2.0;
    double offsetY = (height() - mapHeight) / 2.0;

    for (int r = 0; r < m_gameBoard->getRows(); ++r) {
        for (int c = 0; c < m_gameBoard->getCols(r); ++c) {
            Cell* cell = m_gameBoard->getCell(r, c);
            if (!cell) continue;

            double x = c * horizSpacing + offsetX;
            if (r % 2 == 1)
                x += horizSpacing / 2.0;
            double y = r * vertSpacing + offsetY;

            std::vector<QPointF> hex;
            for (int i = 0; i < 6; ++i) {
                double angle = M_PI / 3.0 * i;
                double dx = hexSize * std::cos(angle);
                double dy = hexSize * std::sin(angle);
                hex.emplace_back(x + dx, y + dy);
            }

            QColor fillColor = Qt::lightGray;
            if (cell->owner == 1)
                fillColor = QColor("#F44336");
            else if (cell->owner == 2)
                fillColor = QColor("#0B0B64");
            else if (cell->terrain == TerrainType::Water)
                fillColor = QColor("#4FC3F7");
            else if (cell->terrain == TerrainType::Rock)
                fillColor = QColor("#546E7A");


            painter.setBrush(fillColor);
            painter.setPen(Qt::black);

            QPolygonF polygon;
            for (const QPointF &pt : hex)
                polygon << pt;

            painter.drawPolygon(polygon);

            QString label = (cell->owner > 0) ? "P" + QString::number(cell->owner) : "";
            painter.setPen(Qt::white);
            painter.drawText(polygon.boundingRect(), Qt::AlignCenter, label);

            if (cell->occupiedAgent) {
                QPixmap agentIcon = cell->occupiedAgent->icon();
                if (!agentIcon.isNull()) {
                    painter.drawPixmap(QRectF(x - hexSize / 1.5, y - hexSize / 1.5, hexSize * 1.5, hexSize * 1.5),
                                       agentIcon, agentIcon.rect());
                }
            }
        }
    }
}

void HexBoardWidget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "HexBoardWidget: dragEnterEvent called. Has custom format:" << event->mimeData()->hasFormat("application/x-yourgame-agent-type");
    if (event->mimeData()->hasFormat("application/x-yourgame-agent-type")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void HexBoardWidget::dropEvent(QDropEvent *event)
{
    qDebug() << "HexBoardWidget: dropEvent called.";
    if (!m_gameBoard) {
        qWarning() << "GameBoard is null in HexBoardWidget::dropEvent!";
        event->ignore();
        return;
    }

    if (!event->mimeData()->hasFormat("application/x-yourgame-agent-type")) {
        qDebug() << "HexBoardWidget: Drop event ignored, wrong MIME format.";
        event->ignore();
        return;
    }

    QPointF dropPos = event->position();
    auto [row, col] = pointToCell(dropPos);
    qDebug() << "HexBoardWidget: Dropped at screen pos:" << dropPos << " -> cell (" << row << "," << col << ")";

    Cell* targetCell = m_gameBoard->getCell(row, col);

    if (targetCell) {
        QByteArray agentData = event->mimeData()->data("application/x-yourgame-agent-type");
        QDataStream stream(&agentData, QIODevice::ReadOnly);
        QString agentTypeName;
        int playerOwner = 0;
        stream >> agentTypeName >> playerOwner;

        qDebug() << "HexBoardWidget: Extracted agent type:" << agentTypeName << " and owner:" << playerOwner;

        Agent* newAgentInstance = createAgentInstance(agentTypeName, playerOwner);
        if (!newAgentInstance) {
            qWarning() << "HexBoardWidget: Failed to create new Agent instance for type:" << agentTypeName;
            event->ignore();
            return;
        }
        qDebug() << "HexBoardWidget: New agent instance created at:" << (void*)newAgentInstance << " named:" << newAgentInstance->name();

        bool isValidPlacement = false;
        if (!targetCell->occupiedAgent) {
            qDebug() << "HexBoardWidget: Target cell is NOT occupied.";
            if (playerOwner == 1 && targetCell->owner == 1) {
                isValidPlacement = true;
                qDebug() << "HexBoardWidget: Valid placement for Player 1 agent in P1 zone.";
            } else if (playerOwner == 2 && targetCell->owner == 2) {
                isValidPlacement = true;
                qDebug() << "HexBoardWidget: Valid placement for Player 2 agent in P2 zone.";
            } else {
                qDebug() << "HexBoardWidget: Invalid owner zone. Dropped by P" << playerOwner << " on P" << targetCell->owner << " zone.";
            }
        } else {
            qDebug() << "HexBoardWidget: Target cell IS ALREADY OCCUPIED by " << (targetCell->occupiedAgent->name());
        }

        if (isValidPlacement) {
            qDebug() << "HexBoardWidget: Attempting to place agent " << newAgentInstance->name() << " at (" << row << "," << col << ") in GameBoard.";
            m_gameBoard->placeAgent(newAgentInstance, row, col);
            update();
            event->acceptProposedAction();
            qDebug() << "HexBoardWidget: Agent placed successfully. Emitting agentPlacedOnBoard signal.";
            emit agentPlacedOnBoard(agentTypeName, playerOwner);
        } else {
            qDebug() << "HexBoardWidget: Invalid placement for agent type" << agentTypeName << " at (" << row << "," << col << ") for player" << playerOwner;
            event->ignore();
            delete newAgentInstance;
            newAgentInstance = nullptr;
        }

    } else {
        qDebug() << "HexBoardWidget: Dropped on invalid cell coordinates (targetCell is NULL).";
        event->ignore();
    }
}


std::pair<int, int> HexBoardWidget::pointToCell(const QPointF &pt) const
{
    if (!m_gameBoard) {
        qWarning() << "GameBoard is null in HexBoardWidget::pointToCell!";
        return {-1, -1};
    }

    double hexSize = 48.0;
    double hexWidth = 2 * hexSize;
    double hexHeight = std::sqrt(3) * hexSize;
    double horizSpacing = hexWidth * 1.5;
    double vertSpacing = hexHeight * 0.5;

    double totalRows = m_gameBoard->getRows();
    double totalCols = 5;
    double mapWidth = (totalCols - 1) * horizSpacing + hexWidth;
    double mapHeight = (totalRows - 1) * vertSpacing + hexHeight;


    double offsetX = (width() - mapWidth) / 2.0;
    double offsetY = (height() - mapHeight) / 2.0;

    for (int r = 0; r < m_gameBoard->getRows(); ++r) {
        for (int c = 0; c < m_gameBoard->getCols(r); ++c) {
            Cell* cell = m_gameBoard->getCell(r, c);
            if (!cell) continue;

            double x = c * horizSpacing + offsetX;
            if (r % 2 == 1)
                x += horizSpacing / 2.0;
            double y = r * vertSpacing + offsetY;

            double dx = pt.x() - x;
            double dy = pt.y() - y;

            if (std::sqrt(dx * dx + dy * dy) <= hexSize) {
                return {r, c};
            }
        }
    }

    return {-1, -1};
}
