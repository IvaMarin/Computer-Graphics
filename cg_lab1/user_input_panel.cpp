#include "user_input_panel.h"

#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QPushButton>

user_input_panel::user_input_panel(QWidget *parent) : QWidget(parent)
{
    QLabel *label_fuction = new QLabel("<p>Вариант 8"
                                       "<br>y = ax<sup>3/2</sup> "
                                       "<br><i>0</i> &lt;&#61; <i>x</i> &lt;&#61; <i>B</i></p>");
    QLabel *label_a_pointer = new QLabel("Параметр a");
    param_a = new QDoubleSpinBox;
    param_a->setDecimals(3);
    param_a->setRange(0.001, 10000);
    param_a->setSingleStep(1);
    param_a->setValue(1);

    QLabel *label_B_pointer = new QLabel("Параметр B");
    param_B = new QDoubleSpinBox;
    param_B->setDecimals(3);
    param_B->setRange(0, 10000);
    param_B->setSingleStep(1);
    param_B->setValue(10);

    QLabel *label_scale = new QLabel("Изменение масштаба");

    plus = new QPushButton("+", this);

    minus = new QPushButton("-", this);

    QVBoxLayout *lout = new QVBoxLayout;
    lout->addWidget(label_fuction);
    lout->addWidget(label_a_pointer);
    lout->addWidget(param_a);
    lout->addWidget(label_B_pointer);
    lout->addWidget(param_B);
    lout->addWidget(label_scale);
    lout->addWidget(plus);
    lout->addWidget(minus);
    lout->addStretch();
    setLayout(lout);


    connect(param_a, SIGNAL(valueChanged(double)), this, SIGNAL(param_a_update(double)));
    connect(param_B, SIGNAL(valueChanged(double)), this, SIGNAL(param_B_update(double)));
    connect(plus, SIGNAL(clicked(bool)), this, SIGNAL(plus_scale(bool)));
    connect(minus, SIGNAL(clicked(bool)), this, SIGNAL(minus_scale(bool)));
}

double user_input_panel::parameter_a() const {
    return param_a->value();
}

double user_input_panel::parameter_B() const {
    return param_B->value();
}
