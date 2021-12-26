#ifndef OBLIQUE_CIRCULAR_CYLINDER_H
#define OBLIQUE_CIRCULAR_CYLINDER_H

#include "light.h"
#include "polygon.h"

#include <QMatrix4x4>
#include <QPainter>

class oblique_circular_cylinder
{
public:
    std::vector<polygon> polygons;
    QMatrix4x4 fullTransformation;

    double approximation_x;
    double approximation_y;
    double approximation_z;

    light *light;
    bool displayCarcass = false;

    oblique_circular_cylinder();
    oblique_circular_cylinder(const oblique_circular_cylinder &cylinder);
    void clear_polygons();
    void change_oblique_circular_cylinder(const QMatrix4x4 &mtrx);
    void set_approximation(double a_x, double a_y, double a_z);
    void create();
    void draw(QPainter *ptr, int center_x, int center_y, double step_pixels_x, double step_pixels_y,
              int window_center_x, int window_center_y);
};

#endif // OBLIQUE_CIRCULAR_CYLINDER_H
