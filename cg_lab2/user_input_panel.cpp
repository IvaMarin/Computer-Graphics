#include "user_input_panel.h"

#include <QVBoxLayout>
#include <QLabel>

user_input_panel::user_input_panel(QWidget *parent) : QWidget(parent)
{

    label_varinat = new QLabel("Вариант 8");
    label_figure = new QLabel("Фигура: 5–гранная прямая правильная призма");
    label_movement = new QLabel("Поворот");
    label_projection = new QLabel("Тип проекции");
    label_scale = new QLabel("Масштабирование");
    label_empty = new QLabel("");

    button_right_ptr = new QPushButton(">", this);
    button_left_ptr = new QPushButton("<", this);
    button_down_ptr = new QPushButton("v", this);
    button_up_ptr = new QPushButton("^", this);
    check_box_display_invisibel_lines_ptr = new QCheckBox("Показывать невидимые линии", this);

    button_rotate_top_projection_ptr = new QPushButton("Вращать ортографическую проекцию на основание", this);
    button_front_projection_ptr = new QCheckBox("Ортографическая проекция на боковую грань", this);
    button_isometric_projection_ptr = new QCheckBox("Изометрическая проекция", this);

    button_plus_ptr = new QPushButton("+", this);
    button_minus_ptr = new QPushButton("-", this);

    QVBoxLayout *lout = new QVBoxLayout;
    lout->addWidget(label_varinat, 0, Qt::AlignHCenter);
    lout->addWidget(label_figure);
    lout->addWidget(label_empty);

    lout->addWidget(label_movement, 0, Qt::AlignHCenter);
    lout->addWidget(button_up_ptr);
    lout->addWidget(button_left_ptr);
    lout->addWidget(button_right_ptr);
    lout->addWidget(button_down_ptr);
    lout->addWidget(label_empty);

    lout->addWidget(label_projection, 0, Qt::AlignHCenter);
    lout->addWidget(button_rotate_top_projection_ptr);
    lout->addWidget(button_front_projection_ptr);
    lout->addWidget(button_isometric_projection_ptr);
    lout->addWidget(label_empty);

    lout->addWidget(label_scale, 0, Qt::AlignHCenter);
    lout->addWidget(button_plus_ptr);
    lout->addWidget(button_minus_ptr);
    lout->addWidget(label_empty);

    lout->addWidget(check_box_display_invisibel_lines_ptr);
    lout->addStretch();
    setLayout(lout);

    connect(button_left_ptr, SIGNAL(pressed()), this, SIGNAL(push_right()));
    connect(button_right_ptr, SIGNAL(pressed()), this, SIGNAL(push_left()));
    connect(button_up_ptr, SIGNAL(pressed()), this, SIGNAL(push_down()));
    connect(button_down_ptr, SIGNAL(pressed()), this, SIGNAL(push_up()));
    connect(check_box_display_invisibel_lines_ptr, SIGNAL(clicked(bool)), this, SIGNAL(clicked_to_display(bool)));

    connect(button_rotate_top_projection_ptr, SIGNAL(pressed()), this, SIGNAL(pressed_top_projection()));
    connect(button_front_projection_ptr, SIGNAL(pressed()), this, SIGNAL(pressed_front_projection()));
    connect(button_isometric_projection_ptr, SIGNAL(pressed()), this, SIGNAL(pressed_isometric_projection()));

    connect(button_plus_ptr, SIGNAL(pressed()), this, SIGNAL(pressed_zoom_in()));
    connect(button_minus_ptr, SIGNAL(pressed()), this, SIGNAL(pressed_zoom_out()));
}


