#ifndef CLIPBOX_H
#define CLIPBOX_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
QT_BEGIN_NAMESPACE
class QLabel;
class QPixmap;
class QPoint;
QT_END_NAMESPACE

class ClipBox : public QWidget
{
    Q_OBJECT

public:
    enum CaptureState{INIT, BEGIN_CAPTURE, BEGIN_MOVE, WAITING,
                      LEFT_TOP_MOVE, LEFT_MOVE, LEFT_BOTTOM_MOVE,
                      BOTTOM_MOVE, RIGHT_BOTTOM_MOVE, RIGHT_MOVE,
                      RIGHT_TOP_MOVE, TOP_MOVE};

    ClipBox(QPixmap pixmap, QWidget *parent = 0);

signals:
    void currentRect(QRect rect);
    void sendEnable();

private:
    CaptureState captureState;
    QPixmap loadPixmap;
    QPixmap capturePixmap;
    QPainter *painter;
    QPoint beginPos, endPos;
    QPoint moveBeginPos, moveEndPos;
    QRect selectRect;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    QRect getSelectRect();
    void drawCaptureImage();
};

#endif // CLIPBOX_H
