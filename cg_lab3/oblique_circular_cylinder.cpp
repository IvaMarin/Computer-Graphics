#include "oblique_circular_cylinder.h"

#include <vector>
#include <cmath>

#include <QVector4D>
#include <QList>
#include <QVector2D>
#include <QTextStream>
#include <QtMath>

oblique_circular_cylinder::oblique_circular_cylinder() {
    approximation_x = 10;
    approximation_y = 10;
    approximation_z = 10;

    light = new class light(70, 0, 0, 100);

    fullTransformation = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

oblique_circular_cylinder::oblique_circular_cylinder(const oblique_circular_cylinder &cylinder) {
    polygons = cylinder.polygons;
    approximation_x = cylinder.approximation_x;
    approximation_y = cylinder.approximation_y;
    approximation_z = cylinder.approximation_z;
}

void oblique_circular_cylinder::clear_polygons() {
    polygons.clear();
}

void oblique_circular_cylinder::change_oblique_circular_cylinder(const QMatrix4x4 &mtrx) {
    for (auto &polygon: polygons) {
        polygon.change_vertices(mtrx);
    }
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

void oblique_circular_cylinder::draw(QPainter *ptr, int center_x, int center_y, double step_pixels_x, double step_pixels_y,
                     int window_center_x, int window_center_y) {
    for (auto &polygon: polygons) {
        auto normal = polygon.get_normal();
        if (normal.z() > 0) {
            polygon.draw(ptr, center_x, center_y, step_pixels_x, step_pixels_y,
                         window_center_x, window_center_y, light, displayCarcass);
        }
    }
}
