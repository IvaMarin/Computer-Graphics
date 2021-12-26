#ifndef POLYGON_H
#define POLYGON_H

#include "light.h"

#include <vector>
#include <map>

#include <QVector4D>
#include <QPainter>
#include <QMatrix4x4>

class polygon
{
public:
    std::vector<QVector4D> vertices;
    std::map<char, int> rgb = {
        {'r', 255},
        {'g', 116},
        {'b', 0}
    };
    double ambient_coef = 0.5;
    double diffuse_coef = 1.5;
    double specular_coef = 1.5;
    double gloss_coef = 4.;

    polygon() = delete;
    polygon(const std::vector<QVector4D> &v);
    QVector3D get_normal();
    void add_vertex(const QVector4D &vertex);
    void add_vertex(double x, double y, double z, double d);
    void clear_verticies();
    void change_vertices(const QMatrix4x4 &mtrx);
    int calc_ambient_component(light *light);
    int calc_diffuse_component(int dx, int dy, light *light);
    int calc_specular_component(int dx, int dy, light *light);
    void draw(QPainter *ptr, int center_x, int center_y, double step_pixels_x, double step_pixels_y,
              int window_center_x, int window_center_y, light *light, bool displayCarcass);
};

#endif // POLYGON_H
