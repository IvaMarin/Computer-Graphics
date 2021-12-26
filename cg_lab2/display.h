#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <prism.h>

using namespace std;

class display : public QWidget
{
    Q_OBJECT
public:
    explicit display(QWidget *parent = nullptr);
    int get_center_x();
    int get_center_y();
    prism &get_prism();

private:
    int center_x;
    int center_y;
    int step;
    prism fig;

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

signals:

};

#endif // DISPLAY_H
