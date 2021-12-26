#ifndef DISPLAY_H
#define DISPLAY_H

#include <oblique_circular_cylinder.h>

#include <QWidget>
#include <QPointF>

class display : public QWidget
{
    Q_OBJECT
public:
    int center_x;
    int center_y;

    double approximation_x;
    double approximation_y;
    double approximation_z;

    oblique_circular_cylinder fig;
    QPointF previousPoint;
    bool is_first;

    explicit display(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:

};
#endif // DISPLAY_H
