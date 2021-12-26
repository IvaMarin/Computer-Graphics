#include "display.h"

#include <cmath>

#include <QPainter>
#include <QResizeEvent>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QColor>

display::display(QWidget *parent) : QWidget(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(213, 198, 198));
    setPalette(pal);

    setAutoFillBackground(true);

    fig.create();

    approximation_x = 10.;
    approximation_y = 10.;
    approximation_z = 10.;

    center_x = 0;
    center_y = 0;

    is_first = true;
}

void display::paintEvent(QPaintEvent *) {
    QPainter ptr{this};
    ptr.setPen(QPen(QColor(255, 5, 0), 0.1));

    if (is_first) {
        center_x = width() / 2;
        center_y = height() / 2;
        is_first = false;
    }

    fig.draw(&ptr, center_x, center_y, approximation_x, approximation_y, width() / 2, height() / 2);
}

void display::resizeEvent(QResizeEvent *event) {
    if (event->oldSize().width() == -1 || event->oldSize().height() == -1)
        return;

    double coef_x = width() / static_cast<double>(event->oldSize().width());
    double coef_y = height() / static_cast<double>(event->oldSize().height());

    center_x *= coef_x;
    center_y *= coef_y;
    update();
}

void display::mousePressEvent(QMouseEvent *event) {
    previousPoint = event->pos();
}

void display::mouseMoveEvent(QMouseEvent *event) {
    QPointF newPoint = event->pos();
    double deltaX = newPoint.x() - previousPoint.x();
    double deltaY = newPoint.y() - previousPoint.y();

    center_x += deltaX;
    center_y += deltaY;

    previousPoint = newPoint;
    update();
}
