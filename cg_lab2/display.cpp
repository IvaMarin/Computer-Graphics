#include "display.h"

#include <vector>
#include <algorithm>
#include <cmath>

#include <QPainter>
#include <QResizeEvent>
#include <QtMath>

display::display(QWidget *parent) : QWidget(parent), step(50)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);

    setAutoFillBackground(true);



    const double number_of_vertices = 5.;

    // bottom penatagon a_b_c_d_e
    vector<double> a{step * cos((2. * M_PI) / number_of_vertices),
                     step * sin((2. * M_PI) / number_of_vertices),
                     static_cast<double>((-1)* step),
                     1};

    vector<double> b{step * cos((2. * M_PI * 2. ) / number_of_vertices),
                     step * sin((2. * M_PI * 2. ) / number_of_vertices),
                     static_cast<double>((-1)* step),
                     1};

    vector<double> c{step * cos((2. * M_PI * 3. ) / number_of_vertices),
                     step * sin((2. * M_PI * 3. ) / number_of_vertices),
                     static_cast<double>((-1)* step),
                     1};

    vector<double> d{step * cos((2. * M_PI * 4. ) / number_of_vertices),
                     step * sin((2. * M_PI * 4. ) / number_of_vertices),
                     static_cast<double>((-1)* step),
                     1};

    vector<double> e{step * cos((2. * M_PI * 5. ) / number_of_vertices),
                     step * sin((2. * M_PI * 5. ) / number_of_vertices),
                     static_cast<double>((-1)* step),
                     1};

    // top pentagon a1_b1_c1_d1_e1
    vector<double> a1{step * cos((2. * M_PI) / number_of_vertices),
                      step * sin((2. * M_PI) / number_of_vertices),
                      static_cast<double>(step),
                      1};

    vector<double> b1{step * cos((2. * M_PI * 2. ) / number_of_vertices),
                      step * sin((2. * M_PI * 2. ) / number_of_vertices),
                      static_cast<double>(step),
                      1};

    vector<double> c1{step * cos((2. * M_PI * 3. ) / number_of_vertices),
                      step * sin((2. * M_PI * 3. ) / number_of_vertices),
                      static_cast<double>(step),
                      1};

    vector<double> d1{step * cos((2. * M_PI * 4. ) / number_of_vertices),
                      step * sin((2. * M_PI * 4. ) / number_of_vertices),
                      static_cast<double>(step),
                      1};

    vector<double> e1{step * cos((2. * M_PI * 5. ) / number_of_vertices),
                      step * sin((2. * M_PI * 5. ) / number_of_vertices),
                      static_cast<double>(step),
                      1};


    polygon p;

    // creating 5 rectangle sides
    p.add_vertex(a);
    p.add_vertex(a1);
    p.add_vertex(e1);
    p.add_vertex(e);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(b);
    p.add_vertex(b1);
    p.add_vertex(a1);
    p.add_vertex(a);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(c);
    p.add_vertex(c1);
    p.add_vertex(b1);
    p.add_vertex(b);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(d);
    p.add_vertex(d1);
    p.add_vertex(c1);
    p.add_vertex(c);
    fig.add_polygon(p);
    p.clear_verticies();

    p.add_vertex(e);
    p.add_vertex(e1);
    p.add_vertex(d1);
    p.add_vertex(d);
    fig.add_polygon(p);
    p.clear_verticies();

    // creating 2 pentagon bases

    // top
    p.add_vertex(a1);
    p.add_vertex(b1);
    p.add_vertex(c1);
    p.add_vertex(d1);
    p.add_vertex(e1);
    fig.add_polygon(p);
    p.clear_verticies();

    // bottom
    p.add_vertex(e);
    p.add_vertex(d);
    p.add_vertex(c);
    p.add_vertex(b);
    p.add_vertex(a);
    fig.add_polygon(p);
    p.clear_verticies();
}

prism &display::get_prism() {
    return fig;
}

void display::paintEvent(QPaintEvent *) {
    QPainter ptr{this};
    ptr.setPen(QPen(Qt::black, 2));

    center_x = width() / 2;
    center_y = height() / 2;


    fig.draw(&ptr, center_x, center_y);

}

void display::resizeEvent(QResizeEvent *event) {
    if (event->oldSize().width() == -1 || event->oldSize().height() == -1)
        return;

    double coef_x = width() / static_cast<double>(event->oldSize().width());
    double coef_y = height() / static_cast<double>(event->oldSize().height());

    center_x *= coef_x;
    center_y *= coef_y;
    update();
}
