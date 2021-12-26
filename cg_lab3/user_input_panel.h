#ifndef USER_INPUT_PANEL_H
#define USER_INPUT_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QVector3D>
#include <QCheckBox>

class user_input_panel : public QWidget
{
    Q_OBJECT
public:
    explicit user_input_panel(QWidget *parent = nullptr);
    void set_cnt_polygons(int cnt);
    void set_light_position(const QVector3D &v);
    QVector3D get_light_position();
    void set_approximation(const double x, const double y, const double z);
    QVector3D get_approximation();
    void set_light_power(int p);
    int get_light_power();

private:
    QLabel *label_scale;
    QLabel *label_empty;

    QPushButton *left;
    QPushButton *right;
    QPushButton *up;
    QPushButton *down;

    QLabel *approximation_x;
    QLineEdit *approximation_x_input;
    QLabel *approximation_y;
    QLineEdit *approximation_y_input;
    QLabel *approximation_z;
    QLineEdit *approximation_z_input;
    QPushButton *apply_approximation;

    QLabel *label_polygons_amount;
    QLabel *cntPolygons;

    QPushButton *zoom_in_btn;
    QPushButton *zoom_out_btn;

    QLabel *light_x;
    QLineEdit *light_x_input;
    QLabel *light_y;
    QLineEdit *light_y_input;
    QLabel *light_z;
    QLineEdit *light_z_input;
    QLabel *light_power;
    QLineEdit *light_power_input;
    QPushButton *apply_light;

    QCheckBox *display_carcass;

signals:
    void push_left();
    void push_right();
    void push_up();
    void push_down();
    void approximation_changed(int);
    void zoom_in();
    void zoom_out();
    void push_apply_light();
    void push_apply_approximation();
    void clicked_display_carcass(bool);
};

#endif // USER_INPUT_PANEL_H

