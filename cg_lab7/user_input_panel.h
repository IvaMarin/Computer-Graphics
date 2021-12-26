#ifndef USER_INPUT_PANEL_H
#define USER_INPUT_PANEL_H


#include <QWidget>
#include <QCheckBox>
#include <QSlider>
#include <QLabel>

class user_input_panel : public QWidget
{
    Q_OBJECT

public:
    explicit user_input_panel(QWidget *parent = nullptr);

private:
    QLabel *nameApproximation;
    QLabel *nameMax;
    QLabel *nameMin;
    QSlider *approximation;
    QCheckBox *dispalyAdditionalLines;

signals:
    void approximation_changed(int);
    void clicked_display_additional_lines(bool);
};

#endif // USER_INPUT_PANEL_H
