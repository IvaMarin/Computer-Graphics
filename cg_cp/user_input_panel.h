#ifndef USER_INPUT_PANEL_H
#define USER_INPUT_PANEL_H


#include <vector>

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>

class user_input_panel : public QWidget
{
    Q_OBJECT

public:
    explicit user_input_panel(QWidget *parent = nullptr);

    float get_light_pos_x();
    float get_light_pos_y();
    float get_light_pos_z();

    void set_light_pos_x(float x);
    void set_light_pos_y(float y);
    void set_light_pos_z(float z);

    std::vector<std::vector<QSpinBox *>> positionsOfPoints;

private:
    QLabel *nameApproximation;
    QSlider *approximation;
    QLabel *nameMax;
    QLabel *nameMin;

    QLabel *label_rotation_x;
    QLabel *label_rotation_y;
    QLabel *label_rotation_z;

    QSlider *pos_fig_x;
    QSlider *pos_fig_y;
    QSlider *pos_fig_z;

    QPushButton *plusScale;
    QPushButton *minusScale;

    QCheckBox *displayCarcass;

    QLabel *firstCurve;
    QLabel *secondCurve;
//    QLabel *thirdCurve;
//    QLabel *fourthCurve;

    QLabel *light_x;
    QLineEdit *light_x_input;
    QLabel *light_y;
    QLineEdit *light_y_input;
    QLabel *light_z;
    QLineEdit *light_z_input;
    QPushButton *apply;

signals:
    void approximation_changed(int);

    void pos_fig_x_changed(int);
    void pos_fig_y_changed(int);
    void pos_fig_z_changed(int);

    void plus_scale();
    void minus_scale();

    void display_carcass(bool);
    void push_apply();

    void first_point_changed_x(int);
    void first_point_changed_y(int);
    void first_point_changed_z(int);

    void second_point_changed_x(int);
    void second_point_changed_y(int);
    void second_point_changed_z(int);

    void third_point_changed_x(int);
    void third_point_changed_y(int);
    void third_point_changed_z(int);

    void fourth_point_changed_x(int);
    void fourth_point_changed_y(int);
    void fourth_point_changed_z(int);

    void fifth_point_changed_x(int);
    void fifth_point_changed_y(int);
    void fifth_point_changed_z(int);

    void sixth_point_changed_x(int);
    void sixth_point_changed_y(int);
    void sixth_point_changed_z(int);

//    void seventh_point_changed_x(int);
//    void seventh_point_changed_y(int);
//    void seventh_point_changed_z(int);

//    void eighth_point_changed_x(int);
//    void eighth_point_changed_y(int);
//    void eighth_point_changed_z(int);

//    void nineth_point_changed_x(int);
//    void nineth_point_changed_y(int);
//    void nineth_point_changed_z(int);

//    void tenth_point_changed_x(int);
//    void tenth_point_changed_y(int);
//    void tenth_point_changed_z(int);

//    void eleventh_point_changed_x(int);
//    void eleventh_point_changed_y(int);
//    void eleventh_point_changed_z(int);

//    void twelfth_point_changed_x(int);
//    void twelfth_point_changed_y(int);
//    void twelfth_point_changed_z(int);
};

#endif // USER_INPUT_PANEL_H
