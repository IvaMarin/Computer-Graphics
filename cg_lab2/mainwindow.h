#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class display;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    display *display_ptr;

private slots:
    void turn_left();
    void turn_right();
    void turn_up();
    void turn_down();
    void display_hidden_lines(bool);
    void top_projection();
    void front_projection();
    void isometric_projection();
    void zoom_in();
    void zoom_out();
};
#endif // MAINWINDOW_H
