#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "display.h"
#include "user_input_panel.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    display *display_ptr;
    user_input_panel *user_input_panel_ptr;
    bool animation;

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void turn_left();
    void turn_right();
    void turn_up();
    void turn_down();

    void plus_scale();
    void minus_scale();

    void change_pos_lamp();
    void display_carcass(bool);

    void change_pos_fig_x(int);
    void change_pos_fig_y(int);
    void change_pos_fig_z(int);

    void change_approximation();

    void on_off_animation();
};

#endif // MAINWINDOW_H
