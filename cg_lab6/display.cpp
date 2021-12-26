#include "display.h"

#include <cmath>

display::display(QWidget *parent)
    : QGLWidget(parent) , fig(oblique_circular_cylinder()) {
    displayCarcass = false;

    rotateX = rotateY = rotateZ = 0.f;
    scale = 0.064f;

    lightPositionX = 1.f;
    lightPositionY = 5.f;
    lightPositionZ = 10.f;

    time = 0.;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animation()));
}

display::~display() {}

void display::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_DEPTH_TEST);
}

void display::resizeGL(int width, int height) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
}

void display::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    anim_draw();

    glDisable(GL_DEPTH_TEST);
}

void display::start_timer() {
    timer->start(100);
}

void display::stop_timer() {
    timer->stop();
}

void display::anim_draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(rotateX, 1.f, 0.f, 0.f);
    glRotatef(rotateY, 0.f, 1.f, 0.f);
    glRotatef(rotateZ, 0.f, 0.f, 1.f);
    glScalef(scale, scale, scale);

    if (displayCarcass) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_LIGHTING);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_LIGHTING);
    }

    glEnable(GL_NORMALIZE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fig.get_ambient_color());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fig.get_diffuse_color());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fig.get_specular_color());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fig.get_shininess());

    float light_ambient[] = {0.f, 0.22f, 0.51f, 1.f};
    float light_diffuse[] = {0.f, 0.55f, 0.128f, 1.f};
    float light_specular[] = {0.f, 0.44f, 0.102f, 1.f};
    float light_position[] = {lightPositionX,
                              lightPositionY,
                              lightPositionZ, 1.f};

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 128);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float distance;
    float x1 = 15 * cos(time),
          y1 = 15 * sin(time),
          z1 = 5;

    for (auto polygon: fig.get_polygons()) {
        glBegin(GL_POLYGON);
            for (auto vertex: polygon.vertices) {
                distance = std::sqrtf((vertex.x() - x1) * (vertex.x() - x1)
                                    + (vertex.y() - y1) * (vertex.y() - y1)
                                    + (vertex.z() - z1) * (vertex.z() - z1));
                glColor4f(0.f, 153.0f, 0.0f, 12.f * static_cast<float>(1 / distance));

                glVertex3f(vertex.x(),
                           vertex.y(),
                           vertex.z());
            }
        glEnd();
    }
    glDisable(GL_BLEND);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void display::animation() {
    time += 0.1;
    update();
}

oblique_circular_cylinder &display::get_fig() {
    return fig;
}

void display::change_display_carcass() {
    displayCarcass = (displayCarcass == true ? false : true);
}

void display::change_angle_rotate_x(float angle) {
    rotateX = static_cast<int>(angle) % 360;
}

void display::change_angle_rotate_y(float angle) {
    rotateY = static_cast<int>(angle) % 360;
}

void display::change_angle_rotate_z(float angle) {
    rotateZ = static_cast<int>(angle) % 360;
}

void display::change_scale(float dif) {
    scale += dif;
}

float display::get_scale() {
    return scale;
}

void display::set_light_position_x(float x_pos) {
    lightPositionX = x_pos;
}

void display::set_light_position_y(float y_pos) {
    lightPositionY = y_pos;
}

void display::set_light_position_z(float z_pos) {
    lightPositionZ = z_pos;
}

float display::get_light_position_x() {
    return lightPositionX;
}

float display::get_light_position_y() {
    return lightPositionY;
}

float display::get_light_position_z() {
    return lightPositionZ;
}
