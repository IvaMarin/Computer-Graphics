#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user_input_panel.h"
#include "widget.h"

#include <QDockWidget>
#include <QResizeEvent>
#include <QAction>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    user_input_panel *panel = new user_input_panel;
    QDockWidget *dock = new QDockWidget("Info");
    dock->setWidget(panel);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    widg = new widget;
    widg->set_panel(panel);
    widg->setMinimumHeight(20);
    widg->setMinimumWidth(20);

    setCentralWidget(widg);

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

    connect(panel, SIGNAL(param_a_update(double)), this, SLOT(redrawOnValueChanged(double)));
    connect(panel, SIGNAL(param_B_update(double)), this, SLOT(redrawOnValueChanged(double)));
    connect(panel, SIGNAL(plus_scale(bool)), this, SLOT(plusScale(bool)));
    connect(panel, SIGNAL(minus_scale(bool)), this, SLOT(minusScale(bool)));
}

void MainWindow::redrawOnValueChanged(double) {
    widg->update();
}

void MainWindow::plusScale(bool) {
    auto s = widg->get_step();
    int upper_bound = 100;
    if (s.first < upper_bound)
        widg->set_step(s.first + 10, s.second + 10);
    widg->update();
}

void MainWindow::minusScale(bool) {
    auto s = widg->get_step();
    int lower_bound = 20;
    if (s.first > lower_bound)
        widg->set_step(s.first - 10, s.second - 10);
    widg->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

