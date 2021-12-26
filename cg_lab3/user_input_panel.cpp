#include "user_input_panel.h"

#include <QGridLayout>

user_input_panel::user_input_panel(QWidget *parent) : QWidget(parent)
{
    label_scale = new QLabel("Масштабирование");
    label_scale->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    label_empty = new QLabel("");

    left = new QPushButton("<", this);
    right = new QPushButton(">", this);
    up = new QPushButton("^", this);
    down = new QPushButton("v", this);
    approximation_x = new QLabel("Аппроксимация X:", this);
    approximation_x->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    approximation_x_input = new QLineEdit(this);
    approximation_y = new QLabel("Аппроксимация Y:", this);
    approximation_y->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    approximation_y_input = new QLineEdit(this);
    approximation_z = new QLabel("Аппроксимация Z:", this);
    approximation_z->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    approximation_z_input = new QLineEdit(this);

    label_polygons_amount = new QLabel("Кол-во полигонов:", this);
    label_polygons_amount->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    cntPolygons = new QLabel(this);
    cntPolygons->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    cntPolygons->setFrameStyle(QFrame::Box);
    zoom_in_btn = new QPushButton("+", this);
    zoom_out_btn = new QPushButton("-", this);
    light_x = new QLabel("Свет X:", this);
    light_x->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    light_x_input = new QLineEdit(this);
    light_y = new QLabel("Свет Y:", this);
    light_y->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    light_y_input = new QLineEdit(this);
    light_z = new QLabel("Свет Z:", this);
    light_z->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    light_z_input = new QLineEdit(this);
    light_power = new QLabel("Мощность:", this);
    light_power->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    light_power_input = new QLineEdit(this);
    apply_light = new QPushButton("Применить", this);
    apply_approximation = new QPushButton("Применить", this);
    display_carcass = new QCheckBox("Показывать каркас", this);

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(up, 0, 1);
    grid->addWidget(left, 1, 0);
    grid->addWidget(down, 1, 1);
    grid->addWidget(right, 1, 2);

    grid->addWidget(label_empty, 2, 0);

    grid->addWidget(label_polygons_amount, 3, 0);
    grid->addWidget(cntPolygons, 3, 1);

    grid->addWidget(label_empty, 4, 0);

    grid->addWidget(label_scale, 5, 0);
    grid->addWidget(zoom_in_btn,5, 1);
    grid->addWidget(zoom_out_btn, 5, 2);

    grid->addWidget(label_empty, 6, 0);

    grid->addWidget(light_x, 7, 0);
    grid->addWidget(light_x_input, 7, 1);
    grid->addWidget(light_y, 8, 0);
    grid->addWidget(light_y_input, 8, 1);
    grid->addWidget(light_z, 9, 0);
    grid->addWidget(light_z_input, 9, 1);
    grid->addWidget(light_power, 10, 0);
    grid->addWidget(light_power_input, 10, 1);
    grid->addWidget(apply_light, 10, 2);

    grid->addWidget(label_empty, 11, 0);

    grid->addWidget(approximation_x, 12, 0);
    grid->addWidget(approximation_x_input, 12, 1);
    grid->addWidget(approximation_y, 13, 0);
    grid->addWidget(approximation_y_input, 13, 1);
    grid->addWidget(approximation_z, 14, 0);
    grid->addWidget(approximation_z_input, 14, 1);
    grid->addWidget(apply_approximation, 14, 2);

    grid->addWidget(label_empty, 15, 0);

    grid->addWidget(display_carcass, 16, 0);

    QVBoxLayout *stretchLout = new QVBoxLayout();
    stretchLout->addStretch();
    grid->addLayout(stretchLout, 17, 0);
    setLayout(grid);

    connect(left, SIGNAL(pressed()), this, SIGNAL(push_left()));
    connect(right, SIGNAL(pressed()), this, SIGNAL(push_right()));
    connect(up, SIGNAL(pressed()), this, SIGNAL(push_up()));
    connect(down, SIGNAL(pressed()), this, SIGNAL(push_down()));
    connect(zoom_in_btn, SIGNAL(pressed()), this, SIGNAL(zoom_in()));
    connect(zoom_out_btn, SIGNAL(pressed()), this, SIGNAL(zoom_out()));
    connect(apply_light, SIGNAL(pressed()), this, SIGNAL(push_apply_light()));
    connect(apply_approximation, SIGNAL(pressed()), this, SIGNAL(push_apply_approximation()));
    connect(display_carcass, SIGNAL(clicked(bool)), this, SIGNAL(clicked_display_carcass(bool)));
}

void user_input_panel::set_cnt_polygons(int cnt) {
    cntPolygons->setNum(cnt);
}

void user_input_panel::set_light_position(const QVector3D &v) {
    light_x_input->setText(QString::number(static_cast<int>(v.x())));
    light_y_input->setText(QString::number(static_cast<int>(v.y())));
    light_z_input->setText(QString::number(static_cast<int>(v.z())));
}

QVector3D user_input_panel::get_light_position() {
    return QVector3D{
        light_x_input->text().toFloat(),
        light_y_input->text().toFloat(),
        light_z_input->text().toFloat()
    };
}

void user_input_panel::set_approximation(const double x, const double y, const double z) {
    approximation_x_input->setText(QString::number(static_cast<int>(x)));
    approximation_y_input->setText(QString::number(static_cast<int>(y)));
    approximation_z_input->setText(QString::number(static_cast<int>(z)));
}

QVector3D user_input_panel::get_approximation() {
    return QVector3D{
        approximation_x_input->text().toFloat(),
        approximation_y_input->text().toFloat(),
        approximation_z_input->text().toFloat()
    };
}

void user_input_panel::set_light_power(int p) {
    light_power_input->setText(QString::number(p));
}

int user_input_panel::get_light_power() {
    return light_power_input->text().toInt();
}
