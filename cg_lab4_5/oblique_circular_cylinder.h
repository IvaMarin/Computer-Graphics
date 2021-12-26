#ifndef OBLIQUE_CIRCULAR_CYLINDER_H
#define OBLIQUE_CIRCULAR_CYLINDER_H


#include "polygon.h"
#include <vector>

class oblique_circular_cylinder
{
private:
    float *ambient_color;
    float *diffuse_color;
    float *specular_color;
    unsigned int shininess;
    std::vector<polygon> polygons;

public:
    double approximation_x;
    double approximation_y;
    double approximation_z;

    oblique_circular_cylinder();
    ~oblique_circular_cylinder();
    oblique_circular_cylinder &operator=(const oblique_circular_cylinder &other);

    const float *get_ambient_color();
    const float *get_diffuse_color();
    const float *get_specular_color();
    unsigned int get_shininess();

    std::vector<polygon> &get_polygons();
    void create();
    void clear_polygons();
    size_t get_polygons_size();
    void set_approximation(double a_x, double a_y, double a_z);
};

#endif // OBLIQUE_CIRCULAR_CYLINDER_H
