#include "user_input_panel.h"

#include <QGridLayout>

user_input_panel::user_input_panel(QWidget *parent) : QWidget(parent)
{
    approximation_x = new QLabel("Аппроксимация X:", this);
    approximation_x->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    approximation_x_input = new QLineEdit(this);
    approximation_y = new QLabel("Аппроксимация Y:", this);
    approximation_y->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    approximation_y_input = new QLineEdit(this);
    approximation_z = new QLabel("Аппроксимация Z:", this);
    approximation_z->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    approximation_z_input = new QLineEdit(this);

    apply_approximation = new QPushButton("Применить", this);

    label_polygons_amount = new QLabel("Кол-во полигонов:", this);
    label_polygons_amount->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    cntPolygons = new QLabel(this);
    cntPolygons->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    cntPolygons->setFrameStyle(QFrame::Box);

    label_scale = new QLabel("Масштабирование");
    label_scale->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    plusScale = new QPushButton("+", this);
    minusScale = new QPushButton("-", this);

    lamp_x = new QLabel("Свет X:", this);
    lamp_x_input = new QLineEdit(this);
    lamp_y = new QLabel("Свет Y:", this);
    lamp_y_input = new QLineEdit(this);
    lamp_z = new QLabel("Свет Z:", this);
    lamp_z_input = new QLineEdit(this);
    apply = new QPushButton("Применить", this);

    display_carcass = new QCheckBox("Показывать каркас", this);

    label_empty = new QLabel("");

    label_rotation_x= new QLabel("Поворот относительно X", this);
    label_rotation_y = new QLabel("Поворот относительно Y", this);
    label_rotation_z = new QLabel("Поворот относительно Z", this);

    pos_fig_x = new QSlider(Qt::Horizontal);
    pos_fig_x->setMinimum(0);
    pos_fig_x->setMaximum(360);
    pos_fig_x->setTickPosition(QSlider::TicksAbove);
    pos_fig_x->setTickInterval(5);
    pos_fig_x->setValue(0);
    pos_fig_y = new QSlider(Qt::Horizontal);
    pos_fig_y->setMinimum(0);
    pos_fig_y->setMaximum(360);
    pos_fig_y->setTickPosition(QSlider::TicksAbove);
    pos_fig_y->setTickInterval(5);
    pos_fig_y->setValue(0);
    pos_fig_z = new QSlider(Qt::Horizontal);
    pos_fig_z->setMinimum(0);
    pos_fig_z->setMaximum(360);
    pos_fig_z->setTickPosition(QSlider::TicksAbove);
    pos_fig_z->setTickInterval(5);
    pos_fig_z->setValue(0);

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(label_polygons_amount, 0, 0);
    grid->addWidget(cntPolygons, 0, 1);

    grid->addWidget(label_empty, 1, 0);

    grid->addWidget(label_scale, 2, 0);
    grid->addWidget(plusScale, 2, 1);
    grid->addWidget(minusScale, 2, 2);

    grid->addWidget(label_empty, 3, 0);

    grid->addWidget(lamp_x, 4, 0);
    grid->addWidget(lamp_x_input, 4, 1);
    grid->addWidget(lamp_y, 5, 0);
    grid->addWidget(lamp_y_input, 5, 1);
    grid->addWidget(lamp_z, 6, 0);
    grid->addWidget(lamp_z_input, 6, 1);
    grid->addWidget(apply, 6, 2);

    grid->addWidget(label_empty, 7, 0);

    grid->addWidget(label_rotation_x, 8, 1);
    grid->addWidget(pos_fig_x, 9, 0, 1, 0);

    grid->addWidget(label_rotation_y, 11, 1);
    grid->addWidget(pos_fig_y, 12, 0, 1, 0);

    grid->addWidget(label_rotation_z, 14, 1);
    grid->addWidget(pos_fig_z, 15, 0, 1, 0);

    grid->addWidget(label_empty, 17, 0);

    grid->addWidget(approximation_x, 18, 0);
    grid->addWidget(approximation_x_input, 18, 1);
    grid->addWidget(approximation_y, 19, 0);
    grid->addWidget(approximation_y_input, 19, 1);
    grid->addWidget(approximation_z, 20, 0);
    grid->addWidget(approximation_z_input, 20, 1);
    grid->addWidget(apply_approximation, 20, 2);

    grid->addWidget(label_empty, 21, 0);

    grid->addWidget(display_carcass, 22, 0);

    QVBoxLayout *stretchLout = new QVBoxLayout();
    stretchLout->addStretch();
    grid->addLayout(stretchLout, 22, 0);
    setLayout(grid);

    connect(plusScale, SIGNAL(pressed()), this, SIGNAL(plus_scale()));
    connect(minusScale, SIGNAL(pressed()), this, SIGNAL(minus_scale()));
    connect(apply, SIGNAL(pressed()), this, SIGNAL(push_apply()));
    connect(display_carcass, SIGNAL(clicked(bool)), this, SIGNAL(clicked_display_carcass(bool)));
    connect(pos_fig_x, SIGNAL(valueChanged(int)), this, SIGNAL(pos_fig_x_changed(int)));
    connect(pos_fig_y, SIGNAL(valueChanged(int)), this, SIGNAL(pos_fig_y_changed(int)));
    connect(pos_fig_z, SIGNAL(valueChanged(int)), this, SIGNAL(pos_fig_z_changed(int)));
    connect(apply_approximation, SIGNAL(pressed()), this, SIGNAL(push_apply_approximation()));
}

void user_input_panel::set_cnt_polygons(size_t cnt) {
    cntPolygons->setNum(static_cast<int>(cnt));
}

float user_input_panel::get_lamp_pos_x() {
    return lamp_x_input->text().toFloat();
}

float user_input_panel::get_lamp_pos_y() {
    return lamp_y_input->text().toFloat();
}

float user_input_panel::get_lamp_pos_z() {
    return lamp_z_input->text().toFloat();
}

void user_input_panel::set_lamp_pos_x(float x) {
    lamp_x_input->setText(QString::number(static_cast<double>(x)));
}

void user_input_panel::set_lamp_pos_y(float y) {
    lamp_y_input->setText(QString::number(static_cast<double>(y)));
}

void user_input_panel::set_lamp_pos_z(float z) {
    lamp_z_input->setText(QString::number(static_cast<double>(z)));
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
