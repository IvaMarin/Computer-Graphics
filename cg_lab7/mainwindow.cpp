#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
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

    QAction *quitAct = new QAction("&Quit", this);
    quitAct->setToolTip("Quit application");
    quitAct->setStatusTip("Closes the application");

    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(quitAct);

    QAction *panelAct = dock->toggleViewAction();
    panelAct->setStatusTip("Toggle panel");

    QMenu *viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction(panelAct);

    precisionValue[0] = 0.025;
    precisionValue[1] = 0.05;
    precisionValue[2] = 0.075;
    precisionValue[3] = 0.1;
    precisionValue[4] = 0.125;
    precisionValue[5] = 0.15;
    precisionValue[6] = 0.175;
    precisionValue[7] = 0.2;
    precisionValue[8] = 0.25;
    precisionValue[9] = 0.3;

    connect(user_input_panel_ptr, SIGNAL(approximation_changed(int)), this, SLOT(change_appr(int)));
    connect(user_input_panel_ptr, SIGNAL(clicked_display_additional_lines(bool)), this, SLOT(display_additional_lines(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change_appr(int sliderValue) {
    display_ptr->set_step(precisionValue[sliderValue - 1]);
    display_ptr->update();
}

void MainWindow::display_additional_lines(bool) {
    display_ptr->change_display_additional_line();
    display_ptr->update();
}
