#include "oblique_circular_cylinder.h"

#include <vector>
#include <cmath>

#include <QVector4D>
#include <QVector2D>
#include <QtMath>
#include <QList>

oblique_circular_cylinder::oblique_circular_cylinder(){
    approximation_x = 40;
    approximation_y = 40;
    approximation_z = 40;

    ambient_color = new float(4);
    ambient_color[0] = 0.2f;
    ambient_color[1] = 0.2f;
    ambient_color[2] = 0.2f;
    ambient_color[3] = 1.f;

    diffuse_color = new float(4);
    diffuse_color[0] = 0.3f;
    diffuse_color[1] = 0.3f;
    diffuse_color[2] = 0.3f;
    diffuse_color[3] = 1.f;

    specular_color = new float(4);
    specular_color[0] = 1.f;
    specular_color[1] = 1.f;
    specular_color[2] = 1.f;
    specular_color[3] = 1.f;

    shininess = 90;

    create();
}

oblique_circular_cylinder::~oblique_circular_cylinder() {}

oblique_circular_cylinder &oblique_circular_cylinder::operator=(const oblique_circular_cylinder &other) {
    approximation_x = other.approximation_x;
    approximation_y = other.approximation_y;
    approximation_z = other.approximation_z;
    polygons = other.polygons;
    return *this;
}

const float *oblique_circular_cylinder::get_ambient_color() {
    return ambient_color;
}

const float *oblique_circular_cylinder::get_diffuse_color() {
    return diffuse_color;
}

const float *oblique_circular_cylinder::get_specular_color() {
    return specular_color;
}

unsigned int oblique_circular_cylinder::get_shininess() {
    return shininess;
}

std::vector<polygon> &oblique_circular_cylinder::get_polygons() {
    return this->polygons;
}

void oblique_circular_cylinder::set_approximation(double a_x, double a_y, double a_z) {
    approximation_x = a_x;
    approximation_y = a_y;
    approximation_z = a_z;
}

void oblique_circular_cylinder::create() {
    int edges = static_cast<int>(approximation_x);
    int radius = 10;
    double height = 10;
    QVector4D shift{2, 2, 0, 0};

    if (edges <= 0 || radius <= 0 || height <= 0) return;

    int layersNum = static_cast<int>(approximation_y);
    int circlesNum = static_cast<int>(approximation_z);

    // base points without relation to top or bottom
    QList<QVector2D> prismBasePoints;

    for (int i = 1; i <= edges; ++i)
    {
        double phi = (M_PI * 2 * i) / edges;
        prismBasePoints.append(radius * QVector2D {static_cast<float>(cos(phi)), static_cast<float>(sin(phi))});
    }
    QList<QVector4D> toPushBack;
    // top base
    for (int i = 0; i < edges; i++) {
        // middle part
        polygons.push_back(std::vector<QVector4D>{
            QVector4D{0, 0, static_cast<float>(height / 2), 1} + shift,
            QVector4D{(prismBasePoints[(i + 1) % edges] / circlesNum), static_cast<float>(height / 2), 1} + shift,
            QVector4D{(prismBasePoints[i] / circlesNum), static_cast<float>(height / 2), 1} + shift});

        // area around middle point
        for (int c = 1; c < circlesNum; ++c) {
           polygons.push_back(std::vector<QVector4D>{
                 QVector4D{(prismBasePoints[i] / circlesNum * c), static_cast<float>(height / 2), 1} + shift,
                 QVector4D{(prismBasePoints[(i + 1) % edges] / circlesNum * c), static_cast<float>(height / 2), 1} + shift,
                 QVector4D{(prismBasePoints[(i + 1) % edges] / circlesNum * (c + 1)), static_cast<float>(height / 2), 1} + shift});
            polygons.push_back(std::vector<QVector4D>{
                 QVector4D{(prismBasePoints[i] / circlesNum * c), static_cast<float>(height / 2), 1} + shift,
                 QVector4D{(prismBasePoints[(i + 1) % edges] / circlesNum * (c + 1)), static_cast<float>(height / 2), 1} + shift,
                 QVector4D{(prismBasePoints[i] / circlesNum * (c + 1)), static_cast<float>(height / 2), 1} + shift});
        }
    }

    // bottom base
    for (int i = 0; i < edges; i++) {
        // middle part
        polygons.push_back(std::vector<QVector4D>{
             QVector4D{0, 0, static_cast<float>(-height / 2), 1} - shift,
             QVector4D{(prismBasePoints[i] / circlesNum), static_cast<float>(-height / 2), 1} - shift,
             QVector4D{(prismBasePoints[(i + 1) % edges] / circlesNum), static_cast<float>(-height / 2), 1} - shift});

        // area around middle point
        for (int c = 1; c < circlesNum; ++c) {
            polygons.push_back(std::vector<QVector4D>{
                 QVector4D{(prismBasePoints[i] / circlesNum * c), static_cast<float>(-height / 2), 1} - shift,
                 QVector4D{(prismBasePoints[(i + 1) % edges] / circlesNum * (c + 1)), static_cast<float>(-height / 2), 1} - shift,
                 QVector4D{(prismBasePoints[(i + 1) % edges] / circlesNum * c), static_cast<float>(-height / 2), 1} - shift});
            polygons.push_back(std::vector<QVector4D>{
                 QVector4D{(prismBasePoints[i] / circlesNum * c), static_cast<float>(-height / 2), 1} - shift,
                 QVector4D{(prismBasePoints[i] / circlesNum * (c + 1)), static_cast<float>(-height / 2), 1} - shift,
                 QVector4D{(prismBasePoints[(i + 1) % edges] / circlesNum * (c + 1)), static_cast<float>(-height / 2), 1} - shift});
        }
    }

    double heightStep = height / layersNum; // step of change in height
    QVector4D shiftStep = shift * 2 / layersNum; // step of shift change

    // polygons that form side surfaces (top is looking up)
    for (int i = 0; i < edges; ++i) {
        QVector4D s = -shiftStep * layersNum / 2;
        for (double h = 0; h < height - heightStep / 4; h += heightStep) {
            polygons.push_back(std::vector<QVector4D>{
                QVector4D{prismBasePoints[i], static_cast<float>(height / 2 - h), 1} - s,
                QVector4D{prismBasePoints[(i + 1) % edges], static_cast<float>(height / 2 - h - heightStep), 1} - s - shiftStep,
                QVector4D{prismBasePoints[i], static_cast<float>(height / 2 - h - heightStep), 1} - s - shiftStep});
            s += shiftStep;
        }
    }

    // polygons that form side surfaces (top is looking down)
    for (int i = 0; i < edges; ++i) {
        QVector4D s = -shiftStep * layersNum / 2;
        for (double h = 0; h < height - heightStep / 4; h += heightStep) {
            polygons.push_back(std::vector<QVector4D>{
                QVector4D{prismBasePoints[i], static_cast<float>(height / 2 - h), 1} - s,
                QVector4D{prismBasePoints[(i + 1) % edges], static_cast<float>(height / 2 - h), 1} - s,
                QVector4D{prismBasePoints[(i + 1) % edges], static_cast<float>(height / 2 - h - heightStep), 1} - s - shiftStep});
            s += shiftStep;
        }
    }
}

void oblique_circular_cylinder::clear_polygons() {
    polygons.clear();
}

size_t oblique_circular_cylinder::get_polygons_size() {
    return polygons.size();
}
