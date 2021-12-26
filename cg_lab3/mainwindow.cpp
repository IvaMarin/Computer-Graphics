#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>

#include <QDockWidget>
#include <QMatrix4x4>
#include <QTextStream>
#include <QtMath>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    user_input_panel_ptr = new user_input_panel();
    QDockWidget *dock = new QDockWidget("Info");
    dock->setWidget(user_input_panel_ptr);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    display_ptr = new display();
    setCentralWidget(display_ptr);

    QAction *quit_action_ptr = new QAction("&Quit", this);
    quit_action_ptr->setToolTip("Quit application");
    quit_action_ptr->setStatusTip("Closes the application");
    connect(quit_action_ptr, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *file_menu_ptr = menuBar()->addMenu("&File");
    file_menu_ptr->addAction(quit_action_ptr);

    QAction *info_action = dock->toggleViewAction();
    info_action->setStatusTip("Toggle panel");

    QMenu *view_menu_ptr = menuBar()->addMenu("&View");
    view_menu_ptr->addAction(info_action);

    user_input_panel_ptr->set_cnt_polygons(static_cast<int>(display_ptr->fig.polygons.size()));
    QVector3D pos_light = display_ptr->fig.light->position;
    user_input_panel_ptr->set_light_position(pos_light);
    int power_light = display_ptr->fig.light->power;
    user_input_panel_ptr->set_light_power(power_light);

    user_input_panel_ptr->set_approximation(display_ptr->fig.approximation_x, display_ptr->fig.approximation_y, display_ptr->fig.approximation_z);

    connect(user_input_panel_ptr, SIGNAL(push_left()), this, SLOT(turn_left()));
    connect(user_input_panel_ptr, SIGNAL(push_right()), this, SLOT(turn_right()));
    connect(user_input_panel_ptr, SIGNAL(push_up()), this, SLOT(turn_up()));
    connect(user_input_panel_ptr, SIGNAL(push_down()), this, SLOT(turn_down()));

    connect(user_input_panel_ptr, SIGNAL(zoom_in()), this, SLOT(zoom_in()));
    connect(user_input_panel_ptr, SIGNAL(zoom_out()), this, SLOT(zoom_out()));
    connect(user_input_panel_ptr, SIGNAL(push_apply_light()), this, SLOT(change_light()));
    connect(user_input_panel_ptr, SIGNAL(push_apply_approximation()), this, SLOT(change_approximation()));
    connect(user_input_panel_ptr, SIGNAL(clicked_display_carcass(bool)), this, SLOT(display_carcass(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::turn_right() {
    QMatrix4x4 matrix_Ry{
        static_cast<float>(cos(-M_PI / 6.)), 0, static_cast<float>(-sin(M_PI / 6.)), 0,
        0, 1, 0, 0,
        static_cast<float>(-sin(-M_PI / 6.)), 0, static_cast<float>(cos(-M_PI / 6.)), 0,
        0, 0, 0, 1
    };

    display_ptr->fig.change_oblique_circular_cylinder(matrix_Ry);
    display_ptr->fig.fullTransformation = matrix_Ry * display_ptr->fig.fullTransformation;
    display_ptr->update();
}

void MainWindow::turn_left() {
    QMatrix4x4 matrix_Ry{
        static_cast<float>(cos(M_PI / 6.)), 0, static_cast<float>(sin(M_PI / 6.)), 0,
        0, 1, 0, 0,
        static_cast<float>(-sin(M_PI / 6.)), 0, static_cast<float>(cos(M_PI / 6.)), 0,
        0, 0, 0, 1
    };

    display_ptr->fig.change_oblique_circular_cylinder(matrix_Ry);
    display_ptr->fig.fullTransformation = matrix_Ry * display_ptr->fig.fullTransformation;
    display_ptr->update();
}

void MainWindow::turn_down() {
    QMatrix4x4 matrix_Rx{
        1, 0, 0, 0,
        0, static_cast<float>(cos(M_PI / 6.)), static_cast<float>(-sin(M_PI / 6.)), 0,
        0, static_cast<float>(sin(M_PI / 6.)), static_cast<float>(cos(M_PI / 6.)), 0,
        0, 0, 0, 1
    };

    display_ptr->fig.change_oblique_circular_cylinder(matrix_Rx);
    display_ptr->fig.fullTransformation = matrix_Rx * display_ptr->fig.fullTransformation;
    display_ptr->update();
}

void MainWindow::turn_up() {
    QMatrix4x4 matrix_Rx{
        1, 0, 0, 0,
        0, static_cast<float>(cos(-M_PI / 6.)), static_cast<float>(-sin(-M_PI / 6.)), 0,
        0, static_cast<float>(sin(-M_PI / 6.)), static_cast<float>(cos(-M_PI / 6.)), 0,
        0, 0, 0, 1
    };

    display_ptr->fig.change_oblique_circular_cylinder(matrix_Rx);
    display_ptr->fig.fullTransformation = matrix_Rx * display_ptr->fig.fullTransformation;
    display_ptr->update();
}

void MainWindow::change_approximation() {
    QTextStream out(stdout);
    display_ptr->fig.set_approximation(user_input_panel_ptr->get_approximation().x(),user_input_panel_ptr->get_approximation().y(),user_input_panel_ptr->get_approximation().z());
    display_ptr->fig.clear_polygons();
    display_ptr->fig.create();
    display_ptr->fig.change_oblique_circular_cylinder(display_ptr->fig.fullTransformation);
    user_input_panel_ptr->set_cnt_polygons(static_cast<int>(display_ptr->fig.polygons.size()));
    display_ptr->update();
}

void MainWindow::zoom_in() {
    double scaling_coefficient = 1.05;
    double coef_x = scaling_coefficient;
    double coef_y = scaling_coefficient;
    double coef_z = scaling_coefficient;
    QMatrix4x4 mtrxS{
        static_cast<float>(coef_x), 0, 0, 0,
        0, static_cast<float>(coef_y), 0, 0,
        0, 0, static_cast<float>(coef_z), 0,
        0, 0, 0, 1
    };
    display_ptr->fig.change_oblique_circular_cylinder(mtrxS);
    display_ptr->fig.fullTransformation = mtrxS * display_ptr->fig.fullTransformation;
    display_ptr->update();
}


void MainWindow::zoom_out() {
    double scaling_coefficient = 0.95;
    double coef_x = scaling_coefficient;
    double coef_y = scaling_coefficient;
    double coef_z = scaling_coefficient;
    QMatrix4x4 mtrxS{
        static_cast<float>(coef_x), 0, 0, 0,
        0, static_cast<float>(coef_y), 0, 0,
        0, 0, static_cast<float>(coef_z), 0,
        0, 0, 0, 1
    };
    display_ptr->fig.change_oblique_circular_cylinder(mtrxS);
    display_ptr->fig.fullTransformation = mtrxS * display_ptr->fig.fullTransformation;
    display_ptr->update();
}

void MainWindow::change_light() {
    display_ptr->fig.light->set_position(user_input_panel_ptr->get_light_position());
    display_ptr->fig.light->set_power(user_input_panel_ptr->get_light_power());
    display_ptr->update();
}

void MainWindow::display_carcass(bool) {
    bool display = display_ptr->fig.displayCarcass;
    display_ptr->fig.displayCarcass = !display;
    display_ptr->update();
}
