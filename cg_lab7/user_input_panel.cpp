#include "user_input_panel.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>

user_input_panel::user_input_panel(QWidget *parent) : QWidget(parent) {
    nameApproximation = new QLabel("Аппроксимация", this);
    nameApproximation->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    nameMax = new QLabel("макс", this);
    nameMax->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    nameMin = new QLabel("мин", this);
    nameMin->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    approximation = new QSlider(Qt::Horizontal);
    approximation->setMinimum(1);
    approximation->setMaximum(10);
    approximation->setTickPosition(QSlider::TicksAbove);
    approximation->setTickInterval(1);
    approximation->setValue(1);

    dispalyAdditionalLines = new QCheckBox("Ломаная", this);

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(nameApproximation, 0, 1);
    grid->addWidget(nameMax, 1, 0);
    grid->addWidget(nameMin, 1, 2);
    grid->addWidget(approximation,2, 0, 2, 0);
    grid->addWidget(dispalyAdditionalLines, 4, 0);

    QVBoxLayout *stretchLout = new QVBoxLayout();
    stretchLout->addStretch();
    grid->addLayout(stretchLout, 5, 0);
    setLayout(grid);

    connect(approximation, SIGNAL(valueChanged(int)), this, SIGNAL(approximation_changed(int)));
    connect(dispalyAdditionalLines, SIGNAL(clicked(bool)), this, SIGNAL(clicked_display_additional_lines(bool)));
}
