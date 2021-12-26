#ifndef DISPLAY_H
#define DISPLAY_H

#include <oblique_circular_cylinder.h>

#include <QWidget>

#include <QOpenGLFunctions>
#include <QGLWidget>

class display : public QGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

private:
    oblique_circular_cylinder fig;

    bool displayCarcass;

    float rotateX;
    float rotateY;
    float rotateZ;

    float scale;

    float lightPositionX;
    float lightPositionY;
    float lightPositionZ;

public:
    double approximation_x;
    double approximation_y;
    double approximation_z;

    display(QWidget *parent = nullptr);
    ~display() override;

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    oblique_circular_cylinder &get_fig();

    void change_display_carcass();

    void change_angle_rotate_x(float angle);
    void change_angle_rotate_y(float angle);
    void change_angle_rotate_z(float angle);

    void change_scale(float dif);
    float get_scale();

    void set_light_position_x(float x_pos);
    void set_light_position_y(float y_pos);
    void set_light_position_z(float z_pos);

    float get_light_position_x();
    float get_light_position_y();
    float get_light_position_z();
};

#endif // DISPLAY_H
