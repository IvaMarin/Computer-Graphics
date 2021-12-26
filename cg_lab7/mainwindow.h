#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "display.h"
#include "user_input_panel.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    display *display_ptr;
    user_input_panel *user_input_panel_ptr;
    double precisionValue[10];

public slots:
    void change_appr(int sliderValue);
    void display_additional_lines(bool);
};

#endif // MAINWINDOW_H
