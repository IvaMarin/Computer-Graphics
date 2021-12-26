#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>

class light
{
public:
    QVector3D position;
    int power;

    light(int p, double x, double y, double z);
    void set_power(const int p);
    void set_position(const QVector3D &v);
    void set_position(const double x, const double y, const double z);
};

#endif // LIGHT_H
