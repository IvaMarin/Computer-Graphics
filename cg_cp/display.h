#ifndef DISPLAY_H
#define DISPLAY_H


#include <vector>

#include <QGLWidget>
#include <QOpenGLFunctions>

#include <QVector4D>
#include <QWidget>

class display : public QGLWidget, public QOpenGLFunctions
{
    float step = 0.025f;
    float scale = 1.;

    float angleX;
    float angleY;
    float angleZ;

    unsigned int cntPoints1;
    unsigned int cntPoints2;
//    unsigned int cntPoints3;
//    unsigned int cntPoints4;

    bool display_carcass = true;

    float lightPositionX;
    float lightPositionY;
    float lightPositionZ;

    std::vector<QVector4D> points1;
    std::vector<QVector4D> points2;
//    std::vector<QVector4D> points3;
//    std::vector<QVector4D> points4;

    void drawBezierCurve(const std::vector<QVector4D> &points);

public:
    display();
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void change_scale(float s);
    void change_display_carcass();

    float get_scale();

    void set_angle_x(float angle);
    void set_angle_y(float angle);
    void set_angle_z(float angle);

    void set_step(float s);

    void change_points1(float val, unsigned int numPoint, unsigned int cord);
    void change_points2(float val, unsigned int numPoint, unsigned int cord);
//    void change_points3(float val, unsigned int numPoint, unsigned int cord);
//    void change_points4(float val, unsigned int numPoint, unsigned int cord);

    void set_light_position_x(float x_pos);
    void set_light_position_y(float y_pos);
    void set_light_position_z(float z_pos);

    float get_light_position_x();
    float get_light_position_y();
    float get_light_position_z();

private:
    float calcX(double t, double v);
    float calcY(double t, double v);
    float calcZ(double t, double v);
};

#endif // DISPLAY_H
