#ifndef POLYGON_H
#define POLYGON_H


#include <vector>

#include <QVector4D>
#include <QVector3D>

class polygon
{
public:
    std::vector<QVector4D> vertices;

    polygon(const std::vector<QVector4D> &v);
    polygon &operator=(const std::vector<QVector4D> &v);
    QVector3D get_normal();
};

#endif // POLYGON_H
