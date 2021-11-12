#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; // window
    w.resize(800, 800); // size of the window
    w.show();
    return a.exec(); // event loop
}
