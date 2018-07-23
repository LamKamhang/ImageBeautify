#include "clipbox.h"
#include <QtWidgets>

ClipBox::ClipBox(QPixmap pixmap, QWidget *parent)
    : QWidget(parent)
    , loadPixmap(pixmap)
    , painter(new QPainter)
    , captureState(INIT)
{
    this->setMouseTracking(true);
    setMinimumHeight(pixmap.height());
    setMinimumWidth(pixmap.width());
}

void ClipBox::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && captureState == INIT){
        beginPos = event->pos();
        captureState = BEGIN_CAPTURE;
        emit sendEnable();
    }
    else if(event->button() == Qt::LeftButton && captureState == WAITING){
        QRect rect = getSelectRect();
        QPoint pos = event->pos();
        if(rect.contains(pos)){
            moveBeginPos = pos;
            if(rect.topLeft() == pos){
                captureState = LEFT_TOP_MOVE;
            } else if(rect.topRight() == pos){
                captureState = RIGHT_TOP_MOVE;
            } else if(rect.bottomLeft() == pos){
                captureState = LEFT_BOTTOM_MOVE;
            } else if(rect.bottomRight() == pos){
                captureState = RIGHT_BOTTOM_MOVE;
            } else if(rect.left() == pos.x()){
                captureState = LEFT_MOVE;
            } else if(rect.right() == pos.x()){
                captureState = RIGHT_MOVE;
            } else if(rect.top() == pos.y()){
                captureState = TOP_MOVE;
            } else if(rect.bottom() == pos.y()){
                captureState = BOTTOM_MOVE;
            } else {
                captureState = BEGIN_MOVE;
            }
        }
    }

    return QWidget::mousePressEvent(event);
}

void ClipBox::mouseReleaseEvent(QMouseEvent *event){
    if(captureState != WAITING && captureState != INIT){
        captureState = WAITING;
    }

    return QWidget::mouseReleaseEvent(event);
}

void ClipBox::mouseMoveEvent(QMouseEvent *event){
    if(captureState == BEGIN_CAPTURE){
        endPos = event->pos();
        update();
    } else if(captureState == WAITING){
        QRect rect = getSelectRect();
        QPoint pos = event->pos();
        if(rect.contains(pos)){
            if(rect.topLeft() == pos || rect.bottomRight() == pos){
                setCursor(Qt::SizeFDiagCursor);
            } else if(rect.topRight() == pos || rect.bottomLeft() == pos){
                setCursor(Qt::SizeBDiagCursor);
            } else if(rect.left() == pos.x() || rect.right() == pos.x()){
                setCursor(Qt::SizeHorCursor);
            } else if(rect.top() == pos.y() || rect.bottom() == pos.y()){
                setCursor(Qt::SizeVerCursor);
            } else {
                setCursor(Qt::SizeAllCursor);
            }
        } else {
            setCursor(Qt::ArrowCursor);
        }
    } else if(captureState != INIT){
        moveEndPos = event->pos();
        int dx = moveEndPos.x() - moveBeginPos.x();
        int dy = moveEndPos.y() - moveBeginPos.y();
        QPoint topLeftPoint, bottomRightPoint;
        topLeftPoint = QPoint(beginPos.x()<=endPos.x()?beginPos.x():endPos.x(),
                              beginPos.y()<=endPos.y()?beginPos.y():endPos.y());
        bottomRightPoint = QPoint(beginPos.x()>=endPos.x()?beginPos.x():endPos.x(),
                                  beginPos.y()>=endPos.y()?beginPos.y():endPos.y());
        if(captureState == BEGIN_MOVE){
            topLeftPoint.setX(beginPos.x() + dx);
            topLeftPoint.setY(beginPos.y() + dy);
            bottomRightPoint.setX(endPos.x() + dx);
            bottomRightPoint.setY(endPos.y() + dy);
        } else if(captureState == LEFT_MOVE){
            topLeftPoint.setX(topLeftPoint.x() + dx);
            if(topLeftPoint.x() > bottomRightPoint.x()){
                captureState = RIGHT_MOVE;
            }
        } else if(captureState == LEFT_TOP_MOVE){
            topLeftPoint.setX(topLeftPoint.x() + dx);
            topLeftPoint.setY(topLeftPoint.y() + dy);
            if(topLeftPoint.x() > bottomRightPoint.x()
                    && topLeftPoint.y() > bottomRightPoint.y()){
                captureState = RIGHT_BOTTOM_MOVE;
            } else if(topLeftPoint.x() > bottomRightPoint.x()){
                captureState = RIGHT_TOP_MOVE;
            } else if(topLeftPoint.y() > bottomRightPoint.y()){
                captureState = LEFT_BOTTOM_MOVE;
            }
        } else if(captureState == TOP_MOVE){
            topLeftPoint.setY(topLeftPoint.y() + dy);
            if(topLeftPoint.y() > bottomRightPoint.y()){
                captureState = BOTTOM_MOVE;
            }
        } else if(captureState == RIGHT_TOP_MOVE){
            bottomRightPoint.setX(bottomRightPoint.x() + dx);
            topLeftPoint.setY(topLeftPoint.y() + dy);
            if(topLeftPoint.x() > bottomRightPoint.x()
                    && topLeftPoint.y() > bottomRightPoint.y()){
                captureState = LEFT_BOTTOM_MOVE;
            } else if(topLeftPoint.x() > bottomRightPoint.x()){
                captureState = LEFT_TOP_MOVE;
            } else if(topLeftPoint.y() > bottomRightPoint.y()){
                captureState = RIGHT_BOTTOM_MOVE;
            }
        } else if(captureState == RIGHT_MOVE){
            bottomRightPoint.setX(bottomRightPoint.x() + dx);
            if(topLeftPoint.x() > bottomRightPoint.x()){
                captureState = LEFT_MOVE;
            }
        } else if(captureState == RIGHT_BOTTOM_MOVE){
            bottomRightPoint.setX(bottomRightPoint.x() + dx);
            bottomRightPoint.setY(bottomRightPoint.y() + dy);
            if(topLeftPoint.x() > bottomRightPoint.x()
                    && topLeftPoint.y() > bottomRightPoint.y()){
                captureState = LEFT_TOP_MOVE;
            } else if(topLeftPoint.x() > bottomRightPoint.x()){
                captureState = LEFT_BOTTOM_MOVE;
            } else if(topLeftPoint.y() > bottomRightPoint.y()){
                captureState = RIGHT_TOP_MOVE;
            }
        } else if(captureState == BOTTOM_MOVE){
            bottomRightPoint.setY(bottomRightPoint.y() + dy);
            if(topLeftPoint.y() > bottomRightPoint.y()){
                captureState = TOP_MOVE;
            }
        } else if(captureState == LEFT_BOTTOM_MOVE){
            topLeftPoint.setX(topLeftPoint.x() + dx);
            bottomRightPoint.setY(bottomRightPoint.y() + dy);
            if(topLeftPoint.x() > bottomRightPoint.x()
                    && topLeftPoint.y() > bottomRightPoint.y()){
                captureState = RIGHT_TOP_MOVE;
            } else if(topLeftPoint.x() > bottomRightPoint.x()){
                captureState = RIGHT_BOTTOM_MOVE;
            } else if(topLeftPoint.y() > bottomRightPoint.y()){
                captureState = LEFT_TOP_MOVE;
            }
        }
        beginPos = topLeftPoint;
        endPos = bottomRightPoint;
        moveBeginPos = moveEndPos;
        update();
    }

    selectRect= getSelectRect();
    emit currentRect(selectRect);

    return QWidget::mouseMoveEvent(event);
}

void ClipBox::paintEvent(QPaintEvent *event){
    painter->begin(this);

    painter->setPen(QPen(Qt::blue, 1, Qt::DashLine, Qt::FlatCap));
    painter->drawPixmap(0, 0, loadPixmap);
    QColor shadowColor = QColor(0, 0, 0, 100);
    painter->fillRect(loadPixmap.rect(), shadowColor);

    switch(captureState){
    case INIT:
        break;
    case BEGIN_CAPTURE:
    case BEGIN_MOVE:
    case LEFT_BOTTOM_MOVE:
    case LEFT_MOVE:
    case LEFT_TOP_MOVE:
    case TOP_MOVE:
    case BOTTOM_MOVE:
    case RIGHT_BOTTOM_MOVE:
    case RIGHT_MOVE:
    case RIGHT_TOP_MOVE:
        drawCaptureImage();
        break;
    default:
        break;
    }

    painter->end();
}

void ClipBox::drawCaptureImage(){
    capturePixmap = loadPixmap.copy(selectRect);
    painter->drawPixmap(selectRect.topLeft(), capturePixmap);
    painter->drawRect(selectRect);
}

QRect ClipBox::getSelectRect(){
    QPoint bpos = beginPos, epos = endPos;
    if(beginPos.x() < 0){
        bpos.setX(0);
    }
    if(endPos.x() < 0){
        epos.setX(0);
    }
    if(beginPos.y() < 0){
        bpos.setY(0);
    }
    if(endPos.y() < 0){
        epos.setY(0);
    }
    int w = loadPixmap.width(), h = loadPixmap.height();
    if(beginPos.x() >= w){
        bpos.setX(w - 1);
    }
    if(endPos.x() >= w){
        epos.setX(w - 1);
    }
    if(beginPos.y() >= h){
        bpos.setY(h - 1);
    }
    if(endPos.y() >= h){
        epos.setY(h - 1);
    }
    int x, y, width, height;
    width = qAbs(bpos.x() - epos.x());
    height = qAbs(bpos.y() - epos.y());
    x = bpos.x() < epos.x() ? bpos.x() : epos.x();
    y = bpos.y() < epos.y() ? bpos.y() : epos.y();

    if(width == 0) width = 1;
    if(height == 0) height = 1;
    return QRect(x, y, width, height);
}

