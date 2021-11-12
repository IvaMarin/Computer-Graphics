#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <utility> //std::pair

using namespace std;

class user_input_panel;

class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = nullptr);
    friend void draw_coord_system(widget *);
    friend void draw_function(widget *);
    void set_panel(user_input_panel *uPl);
    pair<int, int> get_step();
    void set_step(const int &, const int &);

private:
    user_input_panel *uPanel_pointer;
    bool is_first;
    double center_x;
    double center_y;
    double step_x;
    double step_y;
    QPointF previousPoint;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void wheelEvent(QWheelEvent *);

signals:
    void plus_scale(bool);
    void minus_scale(bool);

};

#endif // WIDGET_H
