#include "mainwindow.h"

#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    user_input_panel_ptr = new user_input_panel();
    QDockWidget *dock = new QDockWidget("Info");
    dock->setWidget(user_input_panel_ptr);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    display_ptr = new display();
    setCentralWidget(display_ptr);

    user_input_panel_ptr->set_cnt_polygons(display_ptr->get_fig().get_polygons_size());
    user_input_panel_ptr->set_lamp_pos_x(display_ptr->get_light_position_x());
    user_input_panel_ptr->set_lamp_pos_y(display_ptr->get_light_position_y());
    user_input_panel_ptr->set_lamp_pos_z(display_ptr->get_light_position_z());

    user_input_panel_ptr->set_approximation(display_ptr->get_fig().approximation_x, display_ptr->get_fig().approximation_y, display_ptr->get_fig().approximation_z);

    connect(user_input_panel_ptr, SIGNAL(push_left()), this, SLOT(turn_left()));
    connect(user_input_panel_ptr, SIGNAL(push_right()), this, SLOT(turn_right()));
    connect(user_input_panel_ptr, SIGNAL(push_up()), this, SLOT(turn_up()));
    connect(user_input_panel_ptr, SIGNAL(push_down()), this, SLOT(turn_down()));
    connect(user_input_panel_ptr, SIGNAL(plus_scale()), this, SLOT(plus_scale()));
    connect(user_input_panel_ptr, SIGNAL(minus_scale()), this, SLOT(minus_scale()));
    connect(user_input_panel_ptr, SIGNAL(push_apply()), this, SLOT(change_pos_lamp()));
    connect(user_input_panel_ptr, SIGNAL(clicked_display_carcass(bool)), this, SLOT(display_carcass(bool)));
    connect(user_input_panel_ptr, SIGNAL(pos_fig_x_changed(int)), this, SLOT(change_pos_fig_x(int)));
    connect(user_input_panel_ptr, SIGNAL(pos_fig_y_changed(int)), this, SLOT(change_pos_fig_y(int)));
    connect(user_input_panel_ptr, SIGNAL(pos_fig_z_changed(int)), this, SLOT(change_pos_fig_z(int)));
    connect(user_input_panel_ptr, SIGNAL(push_apply_approximation()), this, SLOT(change_approximation()));
}

void MainWindow::turn_left() {
    display_ptr->change_angle_rotate_y(-10.f);
    display_ptr->updateGL();
}

void MainWindow::turn_right() {
    display_ptr->change_angle_rotate_y(10.f);
    display_ptr->updateGL();
}

void MainWindow::turn_up() {
    display_ptr->change_angle_rotate_x(-10.f);
    display_ptr->updateGL();
}

void MainWindow::turn_down() {
    display_ptr->change_angle_rotate_x(10.f);
    display_ptr->updateGL();
}

void MainWindow::plus_scale() {
    display_ptr->change_scale(0.001f);
    display_ptr->updateGL();
}

void MainWindow::minus_scale() {
    display_ptr->change_scale(-0.001f);
    display_ptr->updateGL();
}

void MainWindow::change_pos_lamp() {
    display_ptr->set_light_position_x(user_input_panel_ptr->get_lamp_pos_x());
    display_ptr->set_light_position_y(user_input_panel_ptr->get_lamp_pos_y());
    display_ptr->set_light_position_z(user_input_panel_ptr->get_lamp_pos_z());
    display_ptr->updateGL();
}

void MainWindow::display_carcass(bool) {
    display_ptr->change_display_carcass();
    display_ptr->updateGL();
}

void MainWindow::change_pos_fig_x(int val) {
    display_ptr->change_angle_rotate_x(val);
    display_ptr->updateGL();
}

void MainWindow::change_pos_fig_y(int val) {
    display_ptr->change_angle_rotate_y(val);
    display_ptr->updateGL();
}

void MainWindow::change_pos_fig_z(int val) {
    display_ptr->change_angle_rotate_z(val);
    display_ptr->updateGL();
}

void MainWindow::change_approximation() {
    display_ptr->get_fig().set_approximation(user_input_panel_ptr->get_approximation().x(),user_input_panel_ptr->get_approximation().y(),user_input_panel_ptr->get_approximation().z());
    display_ptr->get_fig().clear_polygons();
    display_ptr->get_fig().create();
    user_input_panel_ptr->set_cnt_polygons(display_ptr->get_fig().get_polygons_size());
    display_ptr->updateGL();
}
