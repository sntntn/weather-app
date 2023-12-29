#include "GraphDialog.h"

#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>

GraphDialog::GraphDialog(const QVector<int>& temperatures, QWidget *parent)
    : QDialog(parent)
    , m_temperatures(temperatures)
{
    qDebug() << m_temperatures;
    calculateTemperatureRange();
    resize(400, 300);
}

void GraphDialog::resizeEvent(QResizeEvent *event) {
    QDialog::resizeEvent(event);
    update();
}

void GraphDialog::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define margins
    int leftMargin = 60;
    int rightMargin = 10;
    int topMargin = 10;
    int bottomMargin = 50;
    QRect drawingRect = rect().adjusted(leftMargin, topMargin, -rightMargin, -bottomMargin);

    // Draw X and Y axes
    painter.drawLine(drawingRect.bottomLeft(), drawingRect.topLeft());  // Y-axis
    painter.drawLine(drawingRect.bottomLeft(), drawingRect.bottomRight());  // X-axis

    // Time labels on X-axis
    QStringList timeLabels = {"00:00", "06:00", "12:00", "18:00"};
    int hours[] = {0, 6, 12, 18};  // Corresponding hours for the labels
    int labelStep = drawingRect.width() / 23;  // 24 points for 23 intervals
    for (int i = 0; i < 4; ++i) {
        int x = drawingRect.left() + hours[i] * labelStep;  // 4 time steps per label
        painter.drawText(x - painter.fontMetrics().horizontalAdvance(timeLabels[i]) / 2,
                         rect().bottom() - 10, timeLabels[i]);
    }

    // Temperature labels on Y-axis
    double yRange = m_maxTemp - m_minTemp + 6; // +3 for top and bottom
    double yStep = drawingRect.height() / yRange;
    for (int i = m_minTemp - 3; i <= m_maxTemp + 3; i++) {
        int y = drawingRect.bottom() - ((i - (m_minTemp - 3)) * yStep);
        painter.drawText(drawingRect.left() - painter.fontMetrics().horizontalAdvance(QString::number(i)) - 5,
                         y + painter.fontMetrics().height() / 4, QString::number(i));
    }

    // Draw the graph line
    QPen linePen(Qt::blue, 2);
    painter.setPen(linePen);
    QPainterPath path;

    double xScale = static_cast<double>(drawingRect.width()) / 23;  // 24 points for 23 intervals
    double yScale = static_cast<double>(drawingRect.height()) / yRange;

    // Initialize path at the first data point
    QPointF firstPoint(drawingRect.left(), drawingRect.bottom() - ((m_temperatures.first() - (m_minTemp - 3)) * yScale));
    path.moveTo(firstPoint);

    // Draw the graph line
    for (int i = 1; i < m_temperatures.size(); ++i) {
        double x = drawingRect.left() + i * xScale;
        double y = drawingRect.bottom() - ((m_temperatures[i] - (m_minTemp - 3)) * yScale);
        path.lineTo(QPointF(x, y));
    }

    // Complete the fill path
    path.lineTo(QPointF(drawingRect.right(), drawingRect.bottom()));
    path.lineTo(QPointF(drawingRect.left(), drawingRect.bottom()));
    path.closeSubpath();

    // Fill the area under the graph
    QBrush fillBrush(QColor(0, 0, 255, 127)); // Semi-transparent blue
    painter.fillPath(path, fillBrush);

    // Draw the path
    painter.setPen(linePen);
    painter.drawPath(path);
}



void GraphDialog::calculateTemperatureRange()
{
    m_minTemp = *std::min_element(m_temperatures.constBegin(), m_temperatures.constEnd());
    m_maxTemp = *std::max_element(m_temperatures.constBegin(), m_temperatures.constEnd());
}

double GraphDialog::mapTemperatureToY(int temperature) {
    double range = m_maxTemp - m_minTemp;
    if (range == 0) {
        return rect().height() / 2.0; // Avoid division by zero
    }
    double scale = rect().height() / range;
    return rect().bottom() - (temperature - m_minTemp) * scale;
}
