#include "display.h"

#include <cmath>

#include <QMouseEvent>
#include <QPainter>
#include <QPolygon>
#include <QResizeEvent>
#include <QVector2D>


const int SQUARE_SIZE = 10;

display::display(QWidget *parent) : QWidget(parent) {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(179, 179, 179));
    setPalette(pal);

    setAutoFillBackground(true);

    cntPoints = 0;
    points.resize(cntPoints+1);
}

void display::set_step(double s) {
    step = s;
}

void display::change_display_additional_line() {
    if (displayAdditionalLines)
        displayAdditionalLines = false;
    else
        displayAdditionalLines = true;
}

QVector2D display::get_spline_point(double t) {
    int p0, p1, p2, p3;
    p1 = (int)t + 1;
    p2 = p1 + 1;
    p3 = p2 + 1;
    p0 = p1 - 1;

    t -= (int)t;

    double tt = t * t;
    double ttt = tt * t;

    // influential field values
    float q1 =      -ttt + 2.0f*tt - t;
    float q2 =  3.0f*ttt - 5.0f*tt + 2.0f;
    float q3 = -3.0f*ttt + 4.0f*tt + t;
    float q4 =       ttt -      tt;

    float t_x = 0.5f * (points[p0].x() * q1 + points[p1].x() * q2 + points[p2].x() * q3 + points[p3].x() * q4);
    float t_y = 0.5f * (points[p0].y() * q1 + points[p1].y() * q2 + points[p2].y() * q3 + points[p3].y() * q4);

    return {t_x, t_y};
}

void display::paintEvent(QPaintEvent *) {
    QPainter ptr{this};
    ptr.setPen(QColor(0, 0, 0));

    // draws dashed polyline
    if (cntPoints != 0 && displayAdditionalLines) {
        ptr.setPen(Qt::DashLine);
        for (unsigned int i = 0; i < cntPoints - 1; i++) {
            ptr.drawLine(static_cast<int>(points[i].x()) + SQUARE_SIZE / 2,
                         static_cast<int>(points[i].y()) + SQUARE_SIZE / 2,
                         static_cast<int>(points[i + 1].x()) + SQUARE_SIZE / 2,
                         static_cast<int>(points[i + 1].y()) + SQUARE_SIZE / 2);
        }
        ptr.setPen(Qt::SolidLine);
    }

    ptr.setBrush(QColor(0, 0, 0));

    // draws square points of spline
    for (unsigned int i = 0; i < cntPoints; i++) {
        QPolygon pol(QRect(static_cast<int>(points[i].x()),
                           static_cast<int>(points[i].y()),
                           SQUARE_SIZE, SQUARE_SIZE));
        ptr.drawPolygon(pol);
    }

    //draws Catmull-Rom spline
    if (cntPoints > 3) {

        QPen newPen(QColor(138,43,226), 3);
        ptr.setPen(newPen);
        double prevX = points[1].x() + SQUARE_SIZE / 2;
        double prevY = points[1].y() + SQUARE_SIZE / 2;
        for (float t = 0; t < (float)points.size() - 4.0f; t += step) {
            QVector2D pos = get_spline_point(t);
            double x =  pos.x() + SQUARE_SIZE / 2;
            double y =  pos.y() + SQUARE_SIZE / 2;

            ptr.drawLine(static_cast<int>(prevX),
                         static_cast<int>(prevY),
                         static_cast<int>(x),
                         static_cast<int>(y));
            prevX = x;
            prevY = y;

            // setting connection to the last point according to the approximation
            if (t + step >= (float)points.size() - 4.0f) {
                x = points[points.size() - 3].x() + SQUARE_SIZE / 2;
                y = points[points.size() - 3].y() + SQUARE_SIZE / 2;
                ptr.drawLine(static_cast<int>(prevX),
                             static_cast<int>(prevY),
                             static_cast<int>(x),
                             static_cast<int>(y));
            }
        }
    }
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
    if (event->button() == Qt::MiddleButton) {
        points[cntPoints] = event->pos();
        cntPoints++;
        points.resize(cntPoints+1);
    }
    update();
}

void display::mouseMoveEvent(QMouseEvent *event) {
    for (unsigned int i = 0; i < cntPoints; i++) {
        if (event->pos().x() >= points[i].x() - 20 && event->pos().x() <= points[i].x() + 20 &&
            event->pos().y() >= points[i].y() - 20 && event->pos().y() <= points[i].y() + 20) {
            points[i] = event->pos();
            break;
        }
    }
    update();
}
