#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "display.h"
#include "user_input_panel.h"

#include <cmath>

#include <QAction>
#include <QDockWidget>
#include <QTextStream>
#include <QtMath>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    user_input_panel *user_input_panel_ptr = new user_input_panel;
    QDockWidget *dock_widget_ptr = new QDockWidget("Info");
    dock_widget_ptr->setWidget(user_input_panel_ptr);
    addDockWidget(Qt::RightDockWidgetArea, dock_widget_ptr);

    display_ptr = new display;
    setCentralWidget(display_ptr);

    QAction *quit_action_ptr = new QAction("&Quit", this);
    quit_action_ptr->setToolTip("Quit application");
    quit_action_ptr->setStatusTip("Closes the application");
    connect(quit_action_ptr, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *file_menu_ptr = menuBar()->addMenu("&File");
    file_menu_ptr->addAction(quit_action_ptr);

    QAction *info_action = dock_widget_ptr->toggleViewAction();
    info_action->setStatusTip("Toggle panel");

    QMenu *view_menu_ptr = menuBar()->addMenu("&View");
    view_menu_ptr->addAction(info_action);

    connect(user_input_panel_ptr, SIGNAL(push_left()), this, SLOT(turn_left()));
    connect(user_input_panel_ptr, SIGNAL(push_right()), this, SLOT(turn_right()));
    connect(user_input_panel_ptr, SIGNAL(push_up()), this, SLOT(turn_up()));
    connect(user_input_panel_ptr, SIGNAL(push_down()), this, SLOT(turn_down()));
    connect(user_input_panel_ptr, SIGNAL(clicked_to_display(bool)), this, SLOT(display_hidden_lines(bool)));

    connect(user_input_panel_ptr, SIGNAL(pressed_top_projection()), this, SLOT(top_projection()));
    connect(user_input_panel_ptr, SIGNAL(pressed_front_projection()), this, SLOT(front_projection()));
    connect(user_input_panel_ptr, SIGNAL(pressed_isometric_projection()), this, SLOT(isometric_projection()));

    connect(user_input_panel_ptr, SIGNAL(pressed_zoom_in()), this, SLOT(zoom_in()));
    connect(user_input_panel_ptr, SIGNAL(pressed_zoom_out()), this, SLOT(zoom_out()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::turn_left() {
    vector<vector<double>> matrix_Ry{
        vector<double>{cos(M_PI / 12.), 0, sin(M_PI / 12.), 0},
        vector<double>{0, 1, 0, 0},
        vector<double>{-sin(M_PI / 12.), 0, cos(M_PI / 12.), 0},
        vector<double>{0, 0, 0, 1}
    };

    display_ptr->get_prism().change_all_polygons(matrix_Ry);
    display_ptr->update();
}

void MainWindow::turn_right() {
    vector<vector<double>> matrix_Ry{
        vector<double>{cos(M_PI / 12.), 0, -sin(M_PI / 12.), 0},
        vector<double>{0, 1, 0, 0},
        vector<double>{sin(M_PI / 12.), 0, cos(M_PI / 12.), 0},
        vector<double>{0, 0, 0, 1}
    };

    display_ptr->get_prism().change_all_polygons(matrix_Ry);
    display_ptr->update();
}

void MainWindow::turn_up() {
    vector<vector<double>> matrix_Rx{
        vector<double>{1, 0, 0, 0},
        vector<double>{0, cos(M_PI / 12.), sin(M_PI / 12.), 0},
        vector<double>{0, -sin(M_PI / 12.), cos(M_PI / 12.), 0},
        vector<double>{0, 0, 0, 1}
    };

    display_ptr->get_prism().change_all_polygons(matrix_Rx);
    display_ptr->update();
}

void MainWindow::turn_down() {
    vector<vector<double>> matrix_Rx{
        vector<double>{1, 0, 0, 0},
        vector<double>{0, cos(M_PI / 12.), -sin(M_PI / 12.), 0},
        vector<double>{0, sin(M_PI / 12.), cos(M_PI / 12.), 0},
        vector<double>{0, 0, 0, 1}
    };

    display_ptr->get_prism().change_all_polygons(matrix_Rx);
    display_ptr->update();
}

void MainWindow::top_projection() {
    vector<vector<double>> matrix_Ry{
        vector<double>{cos(-M_PI / 2.), 0, sin(-M_PI / 2.), 0},
        vector<double>{0, 1, 0, 0},
        vector<double>{-sin(-M_PI / 2.), 0, cos(-M_PI / 2.), 0},
        vector<double>{0, 0, 0, 1}
    };

    vector<vector<double>> matrix_Rx{
        vector<double>{1, 0, 0, 0},
        vector<double>{0, cos(-M_PI / 2.), -sin(-M_PI / 2.), 0},
        vector<double>{0, sin(-M_PI / 2.), cos(-M_PI / 2.), 0},
        vector<double>{0, 0, 0, 1}
    };

    display_ptr->get_prism().change_all_polygons(matrix_Ry);
    display_ptr->get_prism().change_all_polygons(matrix_Rx);
    display_ptr->get_prism().change_all_polygons(matrix_Ry);
    display_ptr->get_prism().change_all_polygons(matrix_Rx);
    display_ptr->get_prism().change_all_polygons(matrix_Rx);

    display_ptr->update();
}

void MainWindow::front_projection() {
    vector<vector<double>> matrix_Rx{
        vector<double>{1, 0, 0, 0},
        vector<double>{0, cos(-M_PI / 2.), -sin(-M_PI / 2.), 0},
        vector<double>{0, sin(-M_PI / 2.), cos(-M_PI / 2.), 0},
        vector<double>{0, 0, 0, 1}
    };

    vector<vector<double>> matrix_Ry{
        vector<double>{cos(M_PI / 2.), 0, sin(M_PI / 2.), 0},
        vector<double>{0, 1, 0, 0},
        vector<double>{-sin(M_PI / 2.), 0, cos(M_PI / 2.), 0},
        vector<double>{0, 0, 0, 1}
    };

    display_ptr->get_prism().change_all_polygons(matrix_Rx);
    display_ptr->get_prism().change_all_polygons(matrix_Ry);
    display_ptr->get_prism().change_all_polygons(matrix_Ry);

    display_ptr->update();
}

void MainWindow::isometric_projection() {
    vector<vector<double>> matrix_Rx{
        vector<double>{1, 0, 0, 0},
        vector<double>{0, cos(-M_PI / 3.), -sin(-M_PI / 3.), 0},
        vector<double>{0, sin(-M_PI / 3.), cos(-M_PI / 3.), 0},
        vector<double>{0, 0, 0, 1}
    };

    vector<vector<double>> matrix_Ry{
        vector<double>{cos(M_PI / 2.), 0, sin(M_PI / 2.), 0},
        vector<double>{0, 1, 0, 0},
        vector<double>{-sin(M_PI / 2.), 0, cos(M_PI / 2.), 0},
        vector<double>{0, 0, 0, 1}
    };

    display_ptr->get_prism().change_all_polygons(matrix_Rx);
    display_ptr->get_prism().change_all_polygons(matrix_Ry);
    display_ptr->get_prism().change_all_polygons(matrix_Ry);

    display_ptr->update();
}

void MainWindow::display_hidden_lines(bool) {
    bool current_display_state = display_ptr->get_prism().get_display_hidden_lines();
    display_ptr->get_prism().set_display_hidden_lines(!current_display_state);

    display_ptr->update();
}

void MainWindow::zoom_in() {
    double scaling_coefficient = 1.05;
    double coef_x = scaling_coefficient;
    double coef_y = scaling_coefficient;
    double coef_z = scaling_coefficient;
    vector<vector<double>> matrix_s{
        vector<double>{coef_x, 0, 0, 0},
        vector<double>{0, coef_y, 0, 0},
        vector<double>{0, 0, coef_z, 0},
        vector<double>{0, 0, 0, 1}
    };
    display_ptr->get_prism().change_all_polygons(matrix_s);

    display_ptr->update();
}

void MainWindow::zoom_out() {
    double scaling_coefficient = 0.95;
    double coef_x = scaling_coefficient;
    double coef_y = scaling_coefficient;
    double coef_z = scaling_coefficient;
    vector<vector<double>> matrix_s{
        vector<double>{coef_x, 0, 0, 0},
        vector<double>{0, coef_y, 0, 0},
        vector<double>{0, 0, coef_z, 0},
        vector<double>{0, 0, 0, 1}
    };
    display_ptr->get_prism().change_all_polygons(matrix_s);

    display_ptr->update();
}


