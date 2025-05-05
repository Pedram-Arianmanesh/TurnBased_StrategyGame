#include "hexboardwidget.h"
#include <QPainter>
#include <QPolygonF>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPixmap>
#include <cmath>

HexBoardWidget::HexBoardWidget(const Board &boardData, QWidget *parent)
    : QWidget(parent), m_board(boardData)
{
    setAcceptDrops(true);
    setMinimumSize(1280, 800);
}

void HexBoardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    double hexSize = 48.0;
    double hexWidth = 2 * hexSize;
    double hexHeight = std::sqrt(3) * hexSize;
    double horizSpacing = hexWidth * 1.5;
    double vertSpacing = hexHeight * 0.5;

    double totalCols = 5;
    double mapWidth = (totalCols - 1) * horizSpacing + hexWidth;
    double mapHeight = 8 * vertSpacing + hexHeight;

    double offsetX = (width() - mapWidth) / 2.0;
    double offsetY = (height() - mapHeight) / 2.0;

    for (const auto &row : m_board) {
        for (const auto &cell : row) {
            int r = cell.row;
            int c = cell.col;

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
            if (cell.owner == 1)
                fillColor = QColor("#F44336");
            else if (cell.owner == 2)
                fillColor = QColor("#0B0B64");
            else if (cell.terrain == TerrainType::Water)
                fillColor = QColor("#4FC3F7");
            else if (cell.terrain == TerrainType::Rock)
                fillColor = QColor("#546E7A");


            painter.setBrush(fillColor);
            painter.setPen(Qt::black);

            QPolygonF polygon;
            for (const QPointF &pt : hex)
                polygon << pt;

            painter.drawPolygon(polygon);

            QString label = (cell.owner > 0) ? "P" + QString::number(cell.owner) : "";
            painter.setPen(Qt::white);
            painter.drawText(polygon.boundingRect(), Qt::AlignCenter, label);

            auto it = m_agentsOnBoard.find({r, c});
            if (it != m_agentsOnBoard.end()) {
                QPixmap agentIcon(":/images/agents/" + it->second + ".png");
                if (!agentIcon.isNull()) {
                    painter.drawPixmap(QRectF(x - hexSize / 1.5, y - hexSize / 1.5, hexSize * 1.5, hexSize * 1.5), agentIcon, agentIcon.rect());
                }
            }
        }
    }
}

void HexBoardWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void HexBoardWidget::dropEvent(QDropEvent *event)
{
    QPointF dropPos = event->position();
    auto [row, col] = pointToCell(dropPos);

    if (row >= 0 && row < static_cast<int>(m_board.size())) {
        for (const auto &cell : m_board[row]) {
            if (cell.col == col && cell.terrain == TerrainType::Free) {
                QString agentName = event->mimeData()->text();
                m_agentsOnBoard[{row, col}] = agentName;
                update();
                break;
            }
        }
    }

    event->acceptProposedAction();
}

std::pair<int, int> HexBoardWidget::pointToCell(const QPointF &pt) const
{
    double hexSize = 48.0;
    double hexWidth = 2 * hexSize;
    double hexHeight = std::sqrt(3) * hexSize;
    double horizSpacing = hexWidth * 1.5;
    double vertSpacing = hexHeight * 0.5;

    double totalCols = 5;
    double mapWidth = (totalCols - 1) * horizSpacing + hexWidth;
    double mapHeight = 8 * vertSpacing + hexHeight;

    double offsetX = (width() - mapWidth) / 2.0;
    double offsetY = (height() - mapHeight) / 2.0;

    for (const auto &row : m_board) {
        for (const auto &cell : row) {
            int r = cell.row;
            int c = cell.col;

            double x = c * horizSpacing + offsetX;
            if (r % 2 == 1)
                x += horizSpacing / 2.0;
            double y = r * vertSpacing + offsetY;

            double dx = pt.x() - x;
            double dy = pt.y() - y;

            if (std::sqrt(dx * dx + dy * dy) <= hexSize)
                return {r, c};
        }
    }

    return {-1, -1};
}
