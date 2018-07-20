#ifndef CURVECANVAS_H
#define CURVECANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
class QPoint;
QT_END_NAMESPACE

class CurveCanvas : public QWidget
{
    Q_OBJECT
public:
    enum CurveType{LINEAR = 0, PIECEWISE_LINEAR, EXPONENTIAL, LOGARITHM};

    CurveCanvas(QWidget *parent = 0, int w = 256);
    void setType(CurveType type);

signals:
    void linearCurveChanged(QPoint, QPoint);
    void pieceLinCurveChanged(QPoint, QPoint);
    void logCurveChanged(double, double);
    void expCurveChanged(double, double);

public slots:

private:
    int width;
    CurveType type;
    QPoint points[2];
    QPoint moveBeginPos;
    QPoint moveEndPos;
    int moveIndex;
    int radius;
    bool moveStart;

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    QPoint posToCanvas(int x, int y);
    QPoint canvasToPos(QPoint p);
    int getMoveIndex(QPoint pos);
};

#endif // CURVECANVAS_H
