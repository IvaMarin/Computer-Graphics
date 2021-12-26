#include "prism.h"

prism::prism() : displayHiddenLines(false) {}

prism::prism(const std::vector<polygon> &p) : prism() {
    polygons = p;
}

void prism::set_display_hidden_lines(bool b) {
    displayHiddenLines = b;
}

bool prism::get_display_hidden_lines() {
    return displayHiddenLines;
}

void prism::change_all_polygons(const std::vector<std::vector<double>> &v) {
    for (auto &it: polygons) {
        it.change_verticies(v);
    }
}

void prism::add_polygon(const polygon &p) {
    polygons.push_back(p);
}

void prism::draw(QPainter *ptr, int center_x, int center_y) {
    for (auto p : polygons) {
        auto p_normal = p.get_normal();
        if (p_normal[2] > 0) { // if z coordinate of normal is greater than zero
            p.draw(ptr, center_x, center_y);
        } else if (displayHiddenLines) {
            QPen new_pen(Qt::gray, 1, Qt::DashLine);
            QPen old_pen = ptr->pen();
            ptr->setPen(new_pen);
            p.draw(ptr, center_x, center_y);
            ptr->setPen(old_pen);
        }
    }
}
