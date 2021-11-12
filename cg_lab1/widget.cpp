#include "widget.h"
#include "user_input_panel.h"

#include <algorithm>
#include <cmath>
#include <utility>

#include <QPainter>
#include <QResizeEvent>
#include <QWheelEvent>

using namespace std;

widget::widget(QWidget *parent) : QWidget(parent), is_first(true), center_x(0), center_y(0), step_x(50), step_y(50) {
   QPalette pal = palette();
   pal.setColor(QPalette::Window, Qt::white);
   setPalette(pal);

   setAutoFillBackground(true);
}

void widget::set_panel(user_input_panel *uP) {
    uPanel_pointer = uP;
    update();
}

void draw_coord_system(widget *w) {
    const int x_unit_segment = 1.; // value of x coordinate division
    const int y_unit_segment = 1.; // value of y coordinate division
    const double pi = atan(1) * 4;

    QPainter ptr{w};
    ptr.setPen(QPen(Qt::black, 3));

    // drawing X axis
    QPoint p1{0, static_cast<int>(w->center_y)};
    QPoint p2{w->width(), static_cast<int>(w->center_y)};
    const int branch_len = 15;

    ptr.drawLine(p1, p2);

    // drawing '>' at the end of X axis
    QPointF p_branch1{static_cast<double>(w->width()), static_cast<double>(w->center_y)};
    QPointF p_branch2{branch_len * cos(-5 * pi / 6) + w->width(),
                branch_len * sin(-5 * pi / 6) + w->center_y};
    ptr.drawLine(p_branch1, p_branch2);
    p_branch2 = {branch_len * cos(5 * pi / 6) + w->width(),
                 branch_len * sin(5 * pi / 6) + w->center_y};
    ptr.drawLine(p_branch1, p_branch2);

    // drawing Y axis
    p1.setX(static_cast<int>(w->center_x));
    p1.setY(0);
    p2.setX(static_cast<int>(w->center_x));
    p2.setY(w->height());
    ptr.drawLine(p1, p2);

    // drawing '>' at the end of y axis
    p_branch1 = {static_cast<double>(w->center_x), 0};
    p_branch2 = {branch_len * cos(pi / 3) + w->center_x,
                branch_len * sin(pi / 3)};
    ptr.drawLine(p_branch1, p_branch2);
    p_branch2 = {branch_len * cos(2 * pi / 3) + w->center_x,
                 branch_len * sin(2 * pi / 3)};
    ptr.drawLine(p_branch1, p_branch2);

    // drawing '0' and 'X' with 'Y'
    ptr.setPen(QPen(Qt::black, 3));
    ptr.drawText(QPointF(w->center_x - (w->step_x / 4), w->center_y + (w->step_y / 2)),
                 QString::number(0));
    ptr.drawText(w->width() - 15, static_cast<int>(w->center_y + 20), "X");
    ptr.drawText(static_cast<int>(w->center_x - 15), 10, "Y");

    // drawing grid
    p_branch1.setY(w->center_y + w->step_y / 16);
    p_branch2.setY(w->center_y - w->step_y / 16);
    p1.setY(0);
    p2.setY(w->height());
    for (int x = static_cast<int>(w->step_x), num = 0; x + w->center_x < w->width() || w->center_x - x > 0;
         x += w->step_x, num += x_unit_segment) {
        // drawing vertical lines of the grid (right half)
        ptr.setPen(Qt::gray);
        p1.setX(static_cast<int>(x + w->center_x));
        p2.setX(static_cast<int>(x + w->center_x));
        ptr.drawLine(p1, p2);

        // drawing scale on positive X axis
        ptr.setPen(QPen(Qt::black, 3));
        p_branch1.setX(x + w->center_x);
        p_branch2.setX(x + w->center_x);
        ptr.drawLine(p_branch1, p_branch2);

        // drawing scale numbers on positive X axis
        ptr.drawText(QPointF(x + w->center_x - w->step_x / 16, static_cast<int>(p_branch1.y()) - w->step_y / 4),
                     QString::number(num + x_unit_segment));

        // drawing vertical lines of the grid (left half)
        ptr.setPen(Qt::gray);
        p1.setX(static_cast<int>(w->center_x - x));
        p2.setX(static_cast<int>(w->center_x - x));
        ptr.drawLine(p1, p2);

        // drawing scale on negative X axis
        ptr.setPen(QPen(Qt::black, 3));
        p_branch1.setX(w->center_x - x);
        p_branch2.setX(w->center_x - x);
        ptr.drawLine(p_branch1, p_branch2);

        // drawing scale numbers on negative X axis
        ptr.drawText(QPointF(w->center_x - x - w->step_x / 6, static_cast<int>(p_branch1.y()) - w->step_y / 4),
                     QString::number(-1 * (num + x_unit_segment)));
    }

    p_branch1.setX(w->center_x + w->step_x / 16);
    p_branch2.setX(w->center_x - w->step_x / 16);
    p1.setX(0);
    p2.setX(w->width());
    for (int y = static_cast<int>(w->step_y), num = 0; y + w->center_y < w->height() || w->center_y - y > 0;
         y += w->step_y, num +=y_unit_segment) {
        // drawing horizontal lines of the grid (lower half)
        ptr.setPen(Qt::gray);
        p1.setY(static_cast<int>(y + w->center_y));
        p2.setY(static_cast<int>(y + w->center_y));
        ptr.drawLine(p1, p2);

        // drawing scale on negatie Y axis
        ptr.setPen(QPen(Qt::black, 3));
        p_branch1.setY(y + w->center_y);
        p_branch2.setY(y + w->center_y);
        ptr.drawLine(p_branch1, p_branch2);

        // drawing scale numbers on negative Y axis
        ptr.drawText(QPointF(static_cast<int>(p_branch1.x()) + w->step_x / 6, w->center_y - y + w->step_y / 6),
                     QString::number(num + y_unit_segment));

        // drawing horizontal lines of the grid (upper half)
        ptr.setPen(Qt::gray);
        p1.setY(static_cast<int>(w->center_y - y));
        p2.setY(static_cast<int>(w->center_y - y));
        ptr.drawLine(p1, p2);

        // drawing scale on positive Y axis
        ptr.setPen(QPen(Qt::black, 3));
        p_branch1.setY(w->center_y - y);
        p_branch2.setY(w->center_y - y);
        ptr.drawLine(p_branch1, p_branch2);

        // drawing scale numbers on positive Y axis
        ptr.drawText(QPointF(static_cast<int>(p_branch1.x()) + w->step_x / 6, w->center_y + y + w->step_y / 6),
                     QString::number(-1 * (num + y_unit_segment)));
    }
}

void draw_function(widget *w) {
    QPainter ptr{w};
    ptr.setPen(QPen(Qt::blue, 3));
    const double param_a = w->uPanel_pointer->parameter_a();
    const double param_B = w->uPanel_pointer->parameter_B();
    const double step = 0.01;
    const double x_unit_segment = 1.; // value of x coordinate division
    const double y_unit_segment = 1.; // value of y coordinate division
    QPointF p1{w->center_x, w->center_y};
    QPointF p2{};
    for (double x = 0.; x <= param_B; x += step) {
        p2 = {x * (w->step_x / x_unit_segment) + w->center_x, w->center_y - (param_a * pow(x, 3. / 2.)) * (w->step_y / y_unit_segment)};
        ptr.drawLine(p1, p2);
        p1 = p2;
    }

}

void widget::paintEvent(QPaintEvent *) {
    if (uPanel_pointer == nullptr) {
        return;
    }
    if (is_first) {
        center_x = width() / 2;
        center_y = height() / 2;
        is_first = false;
    }
    draw_coord_system(this);
    draw_function(this);
}

void widget::mousePressEvent(QMouseEvent *event) {
    previousPoint = event->pos();
}

void widget::mouseMoveEvent(QMouseEvent *event) {
    QPointF newPoint = event->pos();
    double delta_x = newPoint.x() - previousPoint.x();
    double delta_y = newPoint.y() - previousPoint.y();

    center_x += delta_x;
    center_y += delta_y;

    previousPoint = newPoint;
    update();
}

void widget::resizeEvent(QResizeEvent *event) {
    if (event->oldSize().width() == -1 || event->oldSize().height() == -1)
        return;

    double coef_x = width() / static_cast<double>(event->oldSize().width());
    double coef_y = height() / static_cast<double>(event->oldSize().height());

    center_x *= coef_x;
    center_y *= coef_y;
    update();
}

void widget::wheelEvent(QWheelEvent *event) {
    QPoint numDegrees = event->angleDelta() / 8;
    auto s = get_step();
    int upper_bound = 100;
    int lower_bound = 20;
    if (numDegrees.y() > 0 && s.first < upper_bound)
        set_step(s.first + 2, s.second + 2);
    else if (numDegrees.y() <= 0 && s.first > lower_bound)
        set_step(s.first - 2, s.second - 2);

    update();

}

pair<int, int> widget::get_step() {
    return make_pair(step_x, step_y);
}

void widget::set_step(const int &x, const int &y) {
    step_x = x;
    step_y = y;
}
