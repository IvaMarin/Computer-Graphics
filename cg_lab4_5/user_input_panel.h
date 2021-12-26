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
    void set_cnt_polygons(size_t cnt);
    float get_lamp_pos_x();
    float get_lamp_pos_y();
    float get_lamp_pos_z();
    void set_lamp_pos_x(float x);
    void set_lamp_pos_y(float y);
    void set_lamp_pos_z(float z);
    void set_approximation(const double x, const double y, const double z);
    QVector3D get_approximation();

private:
    QLabel *label_empty;

    QPushButton *left;
    QPushButton *right;
    QPushButton *up;
    QPushButton *down;

    QLabel *label_polygons_amount;
    QLabel *cntPolygons;

    QLabel *label_scale;
    QPushButton *plusScale;
    QPushButton *minusScale;

    QLabel *lamp_x;
    QLineEdit *lamp_x_input;
    QLabel *lamp_y;
    QLineEdit *lamp_y_input;
    QLabel *lamp_z;
    QLineEdit *lamp_z_input;
    QLabel *lamp_power;
    QLineEdit *lamp_power_input;
    QPushButton *apply;

    QCheckBox *display_carcass;

    QLabel *label_rotation_x;
    QLabel *label_rotation_y;
    QLabel *label_rotation_z;

    QSlider *pos_fig_x;
    QSlider *pos_fig_y;
    QSlider *pos_fig_z;

    QLabel *approximation_x;
    QLineEdit *approximation_x_input;
    QLabel *approximation_y;
    QLineEdit *approximation_y_input;
    QLabel *approximation_z;
    QLineEdit *approximation_z_input;

    QPushButton *apply_approximation;

signals:
    void push_left();
    void push_right();
    void push_up();
    void push_down();

    void plus_scale();
    void minus_scale();

    void push_apply();

    void clicked_display_carcass(bool);

    void pos_fig_x_changed(int);
    void pos_fig_y_changed(int);
    void pos_fig_z_changed(int);

    void push_apply_approximation();
};

#endif // USER_INPUT_PANEL_H
