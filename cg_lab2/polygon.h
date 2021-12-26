#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <QPainter>

using namespace std;

class polygon
{
    vector<vector<double>> verticies;
    public:
        polygon();
        polygon(const vector<vector<double>> &v);

        vector<double> get_normal();
        void change_verticies(const vector<vector<double>> &v);
        void add_vertex(const vector<double> &v);
        void add_vertex(double x, double y, double z, double d);  // homogeneous coordinates
        void clear_verticies();
        void draw(QPainter *ptr, int center_x, int center_y);
};

#endif // POLYGON_H
