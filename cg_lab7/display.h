#ifndef DISPLAY_H
#define DISPLAY_H


#include <vector>

#include <QWidget>
#include <QPointF>

class display : public QWidget
{
    Q_OBJECT

public:
    explicit display(QWidget *parent = nullptr);
    void set_step(double s);
    void change_display_additional_line();
    QVector2D get_spline_point(double t);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    float step = 0.025f;
    bool displayAdditionalLines = false;
    unsigned int cntPoints;
    std::vector<QPointF> points;
    double center_x;
    double center_y;
};

#endif // DISPLAY_H
