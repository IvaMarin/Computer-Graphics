#ifndef USER_INPUT_PANEL_H
#define USER_INPUT_PANEL_H

#include <QWidget>

class QDoubleSpinBox;
class QPushButton;

class user_input_panel : public QWidget
{
    Q_OBJECT
public:
    explicit user_input_panel(QWidget *parent = nullptr);
    double parameter_a() const;
    double parameter_B() const;

private:
    QDoubleSpinBox *param_a;
    QDoubleSpinBox *param_B;
    QPushButton *plus;
    QPushButton *minus;

signals:
    void param_a_update(double);
    void param_B_update(double);
    void plus_scale(bool);
    void minus_scale(bool);

};

#endif // USER_INPUT_PANEL_H
