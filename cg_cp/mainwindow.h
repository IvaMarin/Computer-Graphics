#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "display.h"
#include "user_input_panel.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    display *display_ptr;
    user_input_panel *user_input_panel_ptr;
    float precisionValue[10];

public slots:
    void change_appr(int sliderValue);

    void change_pos_fig_x(int);
    void change_pos_fig_y(int);
    void change_pos_fig_z(int);

    void plus_scale();
    void minus_scale();

    void display_carcass(bool);
    void change_pos_light();

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

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

