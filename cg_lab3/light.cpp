#include "light.h"

light::light(int p, double x, double y, double z) {
    power = p;
    position.setX(static_cast<float>(x));
    position.setY(static_cast<float>(y));
    position.setZ(static_cast<float>(z));
}

void light::set_power(const int p) {
    power = p;
}

void light::set_position(const QVector3D &v) {
    position = v;
}

void light::set_position(const double x, const double y, const double z) {
    position.setX(static_cast<float>(x));
    position.setY(static_cast<float>(y));
    position.setZ(static_cast<float>(z));
}
