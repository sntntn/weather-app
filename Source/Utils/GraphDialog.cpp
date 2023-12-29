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
    setFixedSize(800, 800);
}

void GraphDialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect drawingRect = rect().adjusted(50, 10, -10, -30); // Adjust for axis labels and padding

    // Draw X and Y axes
    painter.drawLine(drawingRect.bottomLeft(), drawingRect.topLeft());
    painter.drawLine(drawingRect.bottomLeft(), drawingRect.bottomRight());

    // Draw labels for the X axis
    QStringList timeLabels = {"00:00", "06:00", "12:00", "18:00"};
    int labelStep = drawingRect.width() / 24;
    for (int i = 0; i <= 18; i += 6) {
        int x = drawingRect.left() + i * labelStep * 4; // 4 time steps per label
        painter.drawText(x - painter.fontMetrics().horizontalAdvance(timeLabels[i / 6]) / 2,
                         drawingRect.bottom() + 20, timeLabels[i / 6]);
    }

    // Draw labels for the Y axis
    double yStep = drawingRect.height() / (m_maxTemp - m_minTemp);
    for (int i = m_minTemp; i <= m_maxTemp + 3; i += 1) { // Adjust step as needed
        int y = drawingRect.bottom() - (i - m_minTemp) * yStep;
        painter.drawText(drawingRect.left() - painter.fontMetrics().horizontalAdvance(QString::number(i)) - 5,
                         y + painter.fontMetrics().ascent() / 2, QString::number(i));
    }

    // Draw the graph line
    QPen linePen(Qt::blue, 2);
    painter.setPen(linePen);
    QPainterPath path;

    // Move to the first point adjusted to the scale and origin
    double xScale = static_cast<double>(drawingRect.width()) / 23; // 24 points for 23 intervals
    double yScale = static_cast<double>(drawingRect.height()) / (m_maxTemp - m_minTemp);
    QPointF firstPoint(drawingRect.left(), drawingRect.bottom() - (m_temperatures.first() - m_minTemp) * yScale);
    path.moveTo(firstPoint);

    // Plot the points and draw the graph line
    for (int i = 1; i < m_temperatures.size(); ++i) {
        double x = drawingRect.left() + i * xScale;
        double y = drawingRect.bottom() - (m_temperatures[i] - m_minTemp) * yScale;
        path.lineTo(QPointF(x, y));
    }

    // Draw the path
    painter.drawPath(path);

    // Optional: Fill the area under the path
    QBrush fillBrush(QColor(0, 0, 255, 127)); // Semi-transparent blue
    QPainterPath fillPath = path;
    fillPath.lineTo(drawingRect.bottomRight());
    fillPath.lineTo(drawingRect.bottomLeft());
    fillPath.closeSubpath();
    painter.fillPath(fillPath, fillBrush);
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
