#ifndef STRUCTUREELEMENTCANVAS_H
#define STRUCTUREELEMENTCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QJsonArray>
#include <vector>
QT_BEGIN_NAMESPACE
class QPoint;
QT_END_NAMESPACE

class StructureElementCanvas : public QWidget
{
    Q_OBJECT
public:
    StructureElementCanvas(QWidget *parent = 0, int s = 3, int ws = 200);
    void sizeChange(int);
    void getElementArray(std::vector<int> &array);
    void getAnchor(int &x, int &y);
    void setEnabled(bool);

private:
    int size;
    int widgetSize;
    int map[7][7];
    QPoint anchor;
    QPainter *painter;
    bool enabled;

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    QPoint getMapPoint(QPoint);
};

#endif // STRUCTUREELEMENTCANVAS_H
