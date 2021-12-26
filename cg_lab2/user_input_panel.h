#ifndef USER_INPUT_PANEL_H
#define USER_INPUT_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>

class user_input_panel : public QWidget
{
    Q_OBJECT
public:
    explicit user_input_panel(QWidget *parent = nullptr);

private:
    QLabel *label_varinat;
    QLabel *label_figure;
    QLabel *label_movement;
    QLabel *label_projection;
    QLabel *label_scale;
    QLabel *label_empty;

    QPushButton *button_left_ptr;
    QPushButton *button_right_ptr;
    QPushButton *button_up_ptr;
    QPushButton *button_down_ptr;

    QPushButton *button_rotate_top_projection_ptr;
    QCheckBox *button_front_projection_ptr;
    QCheckBox *button_isometric_projection_ptr;

    QCheckBox *check_box_display_invisibel_lines_ptr;

    QPushButton *button_plus_ptr;
    QPushButton *button_minus_ptr;

signals:
    void push_left();
    void push_right();
    void push_up();
    void push_down();

    void clicked_to_display(bool);

    void pressed_top_projection();
    void pressed_front_projection();
    void pressed_isometric_projection();

    void pressed_zoom_in();
    void pressed_zoom_out();
};

#endif // USER_INPUT_PANEL_H
