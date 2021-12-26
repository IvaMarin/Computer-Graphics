#include "mainwindow.h"

#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    user_input_panel_ptr = new user_input_panel();
    QDockWidget *dock = new QDockWidget("Панель");
    dock->setWidget(user_input_panel_ptr);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    display_ptr = new display();
    setCentralWidget(display_ptr);

    precisionValue[0] = 0.025f; precisionValue[1] = 0.05f; precisionValue[2] = 0.075f;
    precisionValue[3] = 0.1f; precisionValue[4] = 0.125f; precisionValue[5] = 0.15f;
    precisionValue[6] = 0.175f; precisionValue[7] = 0.2f; precisionValue[8] = 0.25f;
    precisionValue[9] = 0.3f;

    user_input_panel_ptr->positionsOfPoints[0][0]->setValue(26);
    user_input_panel_ptr->positionsOfPoints[0][1]->setValue(13);
    user_input_panel_ptr->positionsOfPoints[1][0]->setValue(30);
    user_input_panel_ptr->positionsOfPoints[2][0]->setValue(20);
    user_input_panel_ptr->positionsOfPoints[2][1]->setValue(-13);
    user_input_panel_ptr->positionsOfPoints[3][0]->setValue(-26);
    user_input_panel_ptr->positionsOfPoints[3][1]->setValue(13);
    user_input_panel_ptr->positionsOfPoints[4][0]->setValue(-30);
    user_input_panel_ptr->positionsOfPoints[5][0]->setValue(-20);
    user_input_panel_ptr->positionsOfPoints[5][1]->setValue(-13);
//    user_input_panel_ptr->positionsOfPoints[6][0]->setValue(-26);
//    user_input_panel_ptr->positionsOfPoints[6][1]->setValue(13);
//    user_input_panel_ptr->positionsOfPoints[7][1]->setValue(13);
//    user_input_panel_ptr->positionsOfPoints[8][0]->setValue(26);
//    user_input_panel_ptr->positionsOfPoints[8][1]->setValue(13);
//    user_input_panel_ptr->positionsOfPoints[9][0]->setValue(-20);
//    user_input_panel_ptr->positionsOfPoints[9][1]->setValue(-13);
//    user_input_panel_ptr->positionsOfPoints[10][1]->setValue(-13);
//    user_input_panel_ptr->positionsOfPoints[11][0]->setValue(20);
//    user_input_panel_ptr->positionsOfPoints[11][1]->setValue(-13);


    display_ptr->change_points1(26, 0, 0);
    display_ptr->change_points1(13, 0, 1);
    display_ptr->change_points1(30, 1, 0);
    display_ptr->change_points1(20, 2, 0);
    display_ptr->change_points1(-13, 2, 1);

    display_ptr->change_points2(-26, 0, 0);
    display_ptr->change_points2(13, 0, 1);
    display_ptr->change_points2(-30, 1, 0);
    display_ptr->change_points2(-20, 2, 0);
    display_ptr->change_points2(-13, 2, 1);

//    display_ptr->change_points3(-26, 0, 0);
//    display_ptr->change_points3(13, 0, 1);
//    display_ptr->change_points3(13, 1, 1);
//    display_ptr->change_points3(26, 2, 0);
//    display_ptr->change_points3(13, 2, 1);

//    display_ptr->change_points4(-20, 0, 0);
//    display_ptr->change_points4(-13, 0, 1);
//    display_ptr->change_points4(-13, 1, 1);
//    display_ptr->change_points4(20, 2, 0);
//    display_ptr->change_points4(-13, 2, 1);

    connect(user_input_panel_ptr, SIGNAL(approximation_changed(int)), this, SLOT(change_appr(int)));
    connect(user_input_panel_ptr, SIGNAL(pos_fig_x_changed(int)), this, SLOT(change_pos_fig_x(int)));
    connect(user_input_panel_ptr, SIGNAL(pos_fig_y_changed(int)), this, SLOT(change_pos_fig_y(int)));
    connect(user_input_panel_ptr, SIGNAL(pos_fig_z_changed(int)), this, SLOT(change_pos_fig_z(int)));
    connect(user_input_panel_ptr, SIGNAL(plus_scale()), this, SLOT(plus_scale()));
    connect(user_input_panel_ptr, SIGNAL(minus_scale()), this, SLOT(minus_scale()));
    connect(user_input_panel_ptr, SIGNAL(display_carcass(bool)), this, SLOT(display_carcass(bool)));
    connect(user_input_panel_ptr, SIGNAL(push_apply()), this, SLOT(change_pos_light()));

    connect(user_input_panel_ptr, SIGNAL(first_point_changed_x(int)), this, SLOT(first_point_changed_x(int)));
    connect(user_input_panel_ptr, SIGNAL(first_point_changed_y(int)), this, SLOT(first_point_changed_y(int)));
    connect(user_input_panel_ptr, SIGNAL(first_point_changed_z(int)), this, SLOT(first_point_changed_z(int)));

    connect(user_input_panel_ptr, SIGNAL(second_point_changed_x(int)), this, SLOT(second_point_changed_x(int)));
    connect(user_input_panel_ptr, SIGNAL(second_point_changed_y(int)), this, SLOT(second_point_changed_y(int)));
    connect(user_input_panel_ptr, SIGNAL(second_point_changed_z(int)), this, SLOT(second_point_changed_z(int)));

    connect(user_input_panel_ptr, SIGNAL(third_point_changed_x(int)), this, SLOT(third_point_changed_x(int)));
    connect(user_input_panel_ptr, SIGNAL(third_point_changed_y(int)), this, SLOT(third_point_changed_y(int)));
    connect(user_input_panel_ptr, SIGNAL(third_point_changed_z(int)), this, SLOT(third_point_changed_z(int)));

    connect(user_input_panel_ptr, SIGNAL(fourth_point_changed_x(int)), this, SLOT(fourth_point_changed_x(int)));
    connect(user_input_panel_ptr, SIGNAL(fourth_point_changed_y(int)), this, SLOT(fourth_point_changed_y(int)));
    connect(user_input_panel_ptr, SIGNAL(fourth_point_changed_z(int)), this, SLOT(fourth_point_changed_z(int)));

    connect(user_input_panel_ptr, SIGNAL(fifth_point_changed_x(int)), this, SLOT(fifth_point_changed_x(int)));
    connect(user_input_panel_ptr, SIGNAL(fifth_point_changed_y(int)), this, SLOT(fifth_point_changed_y(int)));
    connect(user_input_panel_ptr, SIGNAL(fifth_point_changed_z(int)), this, SLOT(fifth_point_changed_z(int)));

    connect(user_input_panel_ptr, SIGNAL(sixth_point_changed_x(int)), this, SLOT(sixth_point_changed_x(int)));
    connect(user_input_panel_ptr, SIGNAL(sixth_point_changed_y(int)), this, SLOT(sixth_point_changed_y(int)));
    connect(user_input_panel_ptr, SIGNAL(sixth_point_changed_z(int)), this, SLOT(sixth_point_changed_z(int)));

//    connect(user_input_panel_ptr, SIGNAL(seventh_point_changed_x(int)), this, SLOT(seventh_point_changed_x(int)));
//    connect(user_input_panel_ptr, SIGNAL(seventh_point_changed_y(int)), this, SLOT(seventh_point_changed_y(int)));
//    connect(user_input_panel_ptr, SIGNAL(seventh_point_changed_z(int)), this, SLOT(seventh_point_changed_z(int)));

//    connect(user_input_panel_ptr, SIGNAL(eighth_point_changed_x(int)), this, SLOT(eighth_point_changed_x(int)));
//    connect(user_input_panel_ptr, SIGNAL(eighth_point_changed_y(int)), this, SLOT(eighth_point_changed_y(int)));
//    connect(user_input_panel_ptr, SIGNAL(eighth_point_changed_z(int)), this, SLOT(eighth_point_changed_z(int)));

//    connect(user_input_panel_ptr, SIGNAL(nineth_point_changed_x(int)), this, SLOT(nineth_point_changed_x(int)));
//    connect(user_input_panel_ptr, SIGNAL(nineth_point_changed_y(int)), this, SLOT(nineth_point_changed_y(int)));
//    connect(user_input_panel_ptr, SIGNAL(nineth_point_changed_z(int)), this, SLOT(nineth_point_changed_z(int)));

//    connect(user_input_panel_ptr, SIGNAL(tenth_point_changed_x(int)), this, SLOT(tenth_point_changed_x(int)));
//    connect(user_input_panel_ptr, SIGNAL(tenth_point_changed_y(int)), this, SLOT(tenth_point_changed_y(int)));
//    connect(user_input_panel_ptr, SIGNAL(tenth_point_changed_z(int)), this, SLOT(tenth_point_changed_z(int)));

//    connect(user_input_panel_ptr, SIGNAL(eleventh_point_changed_x(int)), this, SLOT(eleventh_point_changed_x(int)));
//    connect(user_input_panel_ptr, SIGNAL(eleventh_point_changed_y(int)), this, SLOT(eleventh_point_changed_y(int)));
//    connect(user_input_panel_ptr, SIGNAL(eleventh_point_changed_z(int)), this, SLOT(eleventh_point_changed_z(int)));

//    connect(user_input_panel_ptr, SIGNAL(twelfth_point_changed_x(int)), this, SLOT(twelfth_point_changed_x(int)));
//    connect(user_input_panel_ptr, SIGNAL(twelfth_point_changed_y(int)), this, SLOT(twelfth_point_changed_y(int)));
//    connect(user_input_panel_ptr, SIGNAL(twelfth_point_changed_z(int)), this, SLOT(twelfth_point_changed_z(int)));
}

MainWindow::~MainWindow() {}

void MainWindow::change_appr(int sliderValue) {
    display_ptr->set_step(precisionValue[sliderValue - 1]);
    display_ptr->updateGL();
}

void MainWindow::change_pos_fig_x(int newAngle) {
    display_ptr->set_angle_x(newAngle);
    display_ptr->updateGL();
}

void MainWindow::change_pos_fig_y(int newAngle) {
    display_ptr->set_angle_y(newAngle);
    display_ptr->updateGL();
}

void MainWindow::change_pos_fig_z(int newAngle) {
    display_ptr->set_angle_z(newAngle);
    display_ptr->updateGL();
}

void MainWindow::plus_scale() {
    display_ptr->change_scale(0.25f);
    display_ptr->updateGL();
}

void MainWindow::minus_scale() {
    if (display_ptr->get_scale() <= 0.25f) {
        return;
    }
    display_ptr->change_scale(-0.25f);
    display_ptr->updateGL();
}

void MainWindow::display_carcass(bool) {
    display_ptr->change_display_carcass();
    display_ptr->updateGL();
}

void MainWindow::change_pos_light() {
    display_ptr->set_light_position_x(user_input_panel_ptr->get_light_pos_x());
    display_ptr->set_light_position_y(user_input_panel_ptr->get_light_pos_y());
    display_ptr->set_light_position_z(user_input_panel_ptr->get_light_pos_z());
    display_ptr->updateGL();
}

void MainWindow::first_point_changed_x(int value) {
    display_ptr->change_points1(static_cast<float>(value), 0, 0);
    display_ptr->updateGL();
}

void MainWindow::first_point_changed_y(int value) {
    display_ptr->change_points1(static_cast<float>(value), 0, 1);
    display_ptr->updateGL();
}

void MainWindow::first_point_changed_z(int value) {
    display_ptr->change_points1(static_cast<float>(value), 0, 2);
    display_ptr->updateGL();
}

void MainWindow::second_point_changed_x(int value) {
    display_ptr->change_points1(static_cast<float>(value), 1, 0);
    display_ptr->updateGL();
}

void MainWindow::second_point_changed_y(int value) {
    display_ptr->change_points1(static_cast<float>(value), 1, 1);
    display_ptr->updateGL();
}

void MainWindow::second_point_changed_z(int value) {
    display_ptr->change_points1(static_cast<float>(value), 1, 2);
    display_ptr->updateGL();
}

void MainWindow::third_point_changed_x(int value) {
    display_ptr->change_points1(static_cast<float>(value), 2, 0);
    display_ptr->updateGL();
}

void MainWindow::third_point_changed_y(int value) {
    display_ptr->change_points1(static_cast<float>(value), 2, 1);
    display_ptr->updateGL();
}

void MainWindow::third_point_changed_z(int value) {
    display_ptr->change_points1(static_cast<float>(value), 2, 2);
    display_ptr->updateGL();
}

void MainWindow::fourth_point_changed_x(int value) {
    display_ptr->change_points2(static_cast<float>(value), 0, 0);
    display_ptr->updateGL();
}

void MainWindow::fourth_point_changed_y(int value) {
    display_ptr->change_points2(static_cast<float>(value), 0, 1);
    display_ptr->updateGL();
}

void MainWindow::fourth_point_changed_z(int value) {
    display_ptr->change_points2(static_cast<float>(value), 0, 2);
    display_ptr->updateGL();
}

void MainWindow::fifth_point_changed_x(int value) {
    display_ptr->change_points2(static_cast<float>(value), 1, 0);
    display_ptr->updateGL();
}

void MainWindow::fifth_point_changed_y(int value) {
    display_ptr->change_points2(static_cast<float>(value), 1, 1);
    display_ptr->updateGL();
}

void MainWindow::fifth_point_changed_z(int value) {
    display_ptr->change_points2(static_cast<float>(value), 1, 2);
    display_ptr->updateGL();
}

void MainWindow::sixth_point_changed_x(int value) {
    display_ptr->change_points2(static_cast<float>(value), 2, 0);
    display_ptr->updateGL();
}

void MainWindow::sixth_point_changed_y(int value) {
    display_ptr->change_points2(static_cast<float>(value), 2, 1);
    display_ptr->updateGL();
}

void MainWindow::sixth_point_changed_z(int value) {
    display_ptr->change_points2(static_cast<float>(value), 2, 2);
    display_ptr->updateGL();
}

//void MainWindow::seventh_point_changed_x(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 0, 0);
//    display_ptr->updateGL();
//}

//void MainWindow::seventh_point_changed_y(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 0, 1);
//    display_ptr->updateGL();
//}

//void MainWindow::seventh_point_changed_z(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 0, 2);
//    display_ptr->updateGL();
//}

//void MainWindow::eighth_point_changed_x(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 1, 0);
//    display_ptr->updateGL();
//}

//void MainWindow::eighth_point_changed_y(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 1, 1);
//    display_ptr->updateGL();
//}

//void MainWindow::eighth_point_changed_z(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 1, 2);
//    display_ptr->updateGL();
//}

//void MainWindow::nineth_point_changed_x(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 2, 0);
//    display_ptr->updateGL();
//}

//void MainWindow::nineth_point_changed_y(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 2, 1);
//    display_ptr->updateGL();
//}

//void MainWindow::nineth_point_changed_z(int value) {
//    display_ptr->change_points3(static_cast<float>(value), 2, 2);
//    display_ptr->updateGL();
//}

//void MainWindow::tenth_point_changed_x(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 0, 0);
//    display_ptr->updateGL();
//}

//void MainWindow::tenth_point_changed_y(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 0, 1);
//    display_ptr->updateGL();
//}

//void MainWindow::tenth_point_changed_z(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 0, 2);
//    display_ptr->updateGL();
//}

//void MainWindow::eleventh_point_changed_x(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 1, 0);
//    display_ptr->updateGL();
//}

//void MainWindow::eleventh_point_changed_y(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 1, 1);
//    display_ptr->updateGL();
//}

//void MainWindow::eleventh_point_changed_z(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 1, 2);
//    display_ptr->updateGL();
//}

//void MainWindow::twelfth_point_changed_x(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 2, 0);
//    display_ptr->updateGL();
//}

//void MainWindow::twelfth_point_changed_y(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 2, 1);
//    display_ptr->updateGL();
//}

//void MainWindow::twelfth_point_changed_z(int value) {
//    display_ptr->change_points4(static_cast<float>(value), 2, 2);
//    display_ptr->updateGL();
//}
