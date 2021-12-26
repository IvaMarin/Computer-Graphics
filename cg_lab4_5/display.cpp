#include "display.h"

display::display(QWidget *parent)
    : QGLWidget(parent) , fig(oblique_circular_cylinder()) {
    displayCarcass = false;
    rotateX = rotateY = rotateZ = 0.f;
    scale = 0.064f;
    lightPositionX = 0.5f;
    lightPositionY = 1.f;
    lightPositionZ = 0.75f;

    approximation_x = 10.;
    approximation_y = 10.;
    approximation_z = 10.;
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

    glPushMatrix();
    glLoadIdentity();
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
    glPopMatrix();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glColor3f(1.f, 0.f, 0.f);
    for (auto polygon: fig.get_polygons()) {
        glBegin(GL_POLYGON);
            for (auto vertex: polygon.vertices) {
                glVertex3f(vertex.x(), vertex.y(), vertex.z());
            }
        glEnd();
    }
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
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
