#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "display.h"
#include "user_input_panel.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    user_input_panel *user_input_panel_ptr;
    display *display_ptr;

private slots:
    void turn_left();
    void turn_right();
    void turn_up();
    void turn_down();
    void change_approximation();
    void zoom_in();
    void zoom_out();
    void change_light();
    void display_carcass(bool);
};
#endif // MAINWINDOW_H

