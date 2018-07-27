#include "curvecanvas.h"
#include <QtWidgets>

CurveCanvas::CurveCanvas(QWidget *parent, int w)
    : QWidget(parent)
    , width(w)
    , type(LINEAR)
    , radius(4)
{
    this->setMouseTracking(true);
    this->setFixedSize(w,w);

    points[0] = posToCanvas(0,0);
    points[1] = posToCanvas(255,255);

    moveIndex = -1;
    moveStart = false;
}

void CurveCanvas::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        moveIndex = getMoveIndex(e->pos());
        if(moveIndex != -1){
            moveBeginPos = e->pos();
            moveStart = true;
        }
    }
}

void CurveCanvas::mouseReleaseEvent(QMouseEvent *e){
    if(!moveStart)return;
    moveStart = false;
    update();
    if(true){
        QPoint leftP, rightP;
        if(points[0].x() <= points[1].x()){
            leftP = points[0];
            rightP = points[1];
        } else {
            leftP = points[1];
            rightP = points[0];
        }
        QPoint newl, newr;
        newl = canvasToPos(leftP);
        newr = canvasToPos(rightP);
        if(type == LINEAR){
            emit linearCurveChanged(newl, newr);
        } else if(type == PIECEWISE_LINEAR){
            emit pieceLinCurveChanged(newl, newr);
        } else if(type == LOGARITHM){
            double b = (log(newr.x() + 1) - log(newl.x() + 1)) / (newr.y() - newl.y());
            double a = newl.y() - log(newl.x() + 1) / b;
            emit logCurveChanged(a, b);
        } else if(type == EXPONENTIAL){
            double b = (log(newr.y() + 1) - log(newl.y() + 1)) / (newr.x() - newl.x());
            double a = newl.x() - log(newl.y() + 1) / b;
            emit expCurveChanged(a, b);
        }
    }

}

void CurveCanvas::mouseMoveEvent(QMouseEvent *e){
    if(moveStart){
        moveEndPos = e->pos();
        int dx = moveEndPos.x() - moveBeginPos.x();
        int dy = moveEndPos.y() - moveBeginPos.y();
        QPoint p = points[moveIndex];
        points[moveIndex] = QPoint(p.x() + dx, p.y() + dy);
        moveBeginPos = e->pos();
        update();

        if(true){
            QPoint leftP, rightP;
            if(points[0].x() <= points[1].x()){
                leftP = points[0];
                rightP = points[1];
            } else {
                leftP = points[1];
                rightP = points[0];
            }
            QPoint newl, newr;
            newl = canvasToPos(leftP);
            newr = canvasToPos(rightP);
            if(type == LINEAR){
                emit linearCurveChanged(newl, newr);
            } else if(type == PIECEWISE_LINEAR){
                emit pieceLinCurveChanged(newl, newr);
            } else if(type == LOGARITHM){
                double b = (log(newr.x() + 1) - log(newl.x() + 1)) / (newr.y() - newl.y());
                double a = newl.y() - log(newl.x() + 1) / b;
                emit logCurveChanged(a, b);
            } else if(type == EXPONENTIAL){
                double b = (log(newr.y() + 1) - log(newl.y() + 1)) / (newr.x() - newl.x());
                double a = newl.x() - log(newl.y() + 1) / b;
                emit expCurveChanged(a, b);
            }
        }
    }
}

void CurveCanvas::paintEvent(QPaintEvent *e){
    if(type == LINEAR || type == PIECEWISE_LINEAR){
        for(int i = 0; i < 2; i++){
            if(points[i].x() < 0){
                if(type == LINEAR) points[i].setX(0);
                else points[i].setX(1);
            } else if(points[i].x() >= width){
                if(type == LINEAR)points[i].setX(width - 1);
                else points[i].setX(width - 2);
            }
            if(points[i].y() < 0){
                if(type == LINEAR) points[i].setY(0);
                else points[i].setY(1);
            } else if(points[i].y() >= width){
                if(type == LINEAR)points[i].setY(width - 1);
                else points[i].setY(width - 2);
            }
        }
    }
    QPainter painter;
    painter.begin(this);
    painter.fillRect(0, 0, width, width, Qt::white);
    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine, Qt::FlatCap));
    for(int i = 1; i < 4; i++){
        painter.drawLine(i * width / 4, 0, i * width / 4, width);
        painter.drawLine(0, i * width / 4, width, i * width / 4);
    }
    painter.drawRect(0, 0, width - 1, width - 1);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    QPoint leftP, rightP;
    if(points[0].x() <= points[1].x()){
        leftP = points[0];
        rightP = points[1];
    } else {
        leftP = points[1];
        rightP = points[0];
    }
    QPoint newl, newr;
    newl = canvasToPos(leftP);
    newr = canvasToPos(rightP);
    if(type == LINEAR){
        painter.drawLine(QPoint(0, leftP.y()), leftP);
        painter.drawLine(leftP, rightP);
        painter.drawLine(rightP, QPoint(256, rightP.y()));
    } else if(type == LOGARITHM){
        double b = (log(newr.x() + 1) - log(newl.x() + 1)) / (newr.y() - newl.y());
        double a = newl.y() - log(newl.x() + 1) / b;
        for(int i = 0; i < width; i++){
            double x = i * 256.0 / width;
            double y = a + log(x+1) / b;
            int j = (int)(y * width / 256);
            if(j>=0 && j < width)painter.drawPoint(posToCanvas(i,j));
        }
        for(int j = 0; j < width; j++){
            double y = j * 256.0 / width;
            double x = exp(b*(y - a)) - 1;
            int i = (int)(x * width / 256);
            if(i>=0 && i < width)painter.drawPoint(posToCanvas(i,j));
        }
    } else if(type == PIECEWISE_LINEAR){
        painter.drawLine(posToCanvas(0, 0), leftP);
        painter.drawLine(leftP, rightP);
        painter.drawLine(rightP, posToCanvas(255, 255));
    } else {
        double b = (log(newr.y()+1) - log(newl.y()+1)) / (newr.x()-newl.x());
        double a = newl.x() - log(newl.y()+1) / b;
        for(int i = 0; i < width; i++){
            double x = i * 256.0 / width;
            double y = exp(b*(x - a)) - 1;
            int j = (int)(y * width / 256);
            if(j>=0 && j < width)painter.drawPoint(posToCanvas(i,j));
        }
        for(int j = 0; j < width; j++){
            double y = j * 256.0 / width;
            double x = a + log(y+1) / b;
            int i = (int)(x * width / 256);
            if(i>=0 && i < width)painter.drawPoint(posToCanvas(i,j));
        }
    }
    QPainterPath path;
    path.addEllipse(leftP.x() - radius, leftP.y() - radius, 2*radius, 2*radius);
    path.addEllipse(rightP.x() - radius, rightP.y() - radius, 2*radius, 2*radius);
    path.setFillRule(Qt::WindingFill);
    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(Qt::red);
    painter.drawPath(path);
    if(moveStart){
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawText(leftP, tr("(%1,%2)").arg(newl.x()).arg(newl.y()));
        painter.drawText(rightP, tr("(%1,%2)").arg(newr.x()).arg(newr.y()));
    }
    painter.end();
}

int CurveCanvas::getMoveIndex(QPoint pos){
    for(int i = 0; i < 2; i++){
        QPoint p = points[i];
        double distance = sqrt(pow(pos.x()-p.x(), 2) + pow(pos.y()-p.y(), 2));
        if(distance <= radius){
            return i;
        }
    }
    return -1;
}

void CurveCanvas::setType(CurveType t){
    type = t;
    update();
}

QPoint CurveCanvas::posToCanvas(int x, int y){
    x = x * (double)width / 256;
    y = (255 - y) * (double)width / 256;
    return QPoint(x,y);
}

QPoint CurveCanvas::canvasToPos(QPoint p){
    int x = p.x() * 256.0 / width;
    int y = 255 - p.y() * 256.0 / width;
    return QPoint(x,y);
}
