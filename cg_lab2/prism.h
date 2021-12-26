#ifndef PRISM_H
#define PRISM_H

#include <polygon.h>

using namespace std;

class prism
{
private:
    vector<polygon> polygons;
    bool displayHiddenLines;

public:
    prism();
    prism(const vector<polygon> &p);

    void set_display_hidden_lines(bool b);
    bool get_display_hidden_lines();
    void change_all_polygons(const vector<vector<double>> &v);
    void add_polygon(const polygon &p);
    void draw(QPainter *ptr, int center_x, int center_y);
};

#endif // PRISM_H
