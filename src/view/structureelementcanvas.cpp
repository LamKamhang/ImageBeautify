#include "structureelementcanvas.h"
#include <QtWidgets>

StructureElementCanvas::StructureElementCanvas(QWidget *parent, int s, int ws)
    : QWidget(parent)
    , size(s)
    , widgetSize(ws)
    , painter(new QPainter)
{
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            map[i][j] = 1;
        }
    }
    anchor = QPoint(1, 1);
    this->setMouseTracking(true);
    setFixedSize(widgetSize, widgetSize);
    enabled = true;
}

void StructureElementCanvas::mousePressEvent(QMouseEvent *e){
    if(!enabled){
        return QWidget::mousePressEvent(e);
    }
    QPoint pos = getMapPoint(e->pos());
    if(e->button()==Qt::LeftButton){
        map[pos.x()][pos.y()] = 1 - map[pos.x()][pos.y()];
    } else if(e->button()==Qt::RightButton){
        anchor = pos;
    }
    update();
    return QWidget::mousePressEvent(e);
}

QPoint StructureElementCanvas::getMapPoint(QPoint p){
    int x = p.x() * size / widgetSize;
    int y = p.y() * size / widgetSize;
    return QPoint(x, y);
}

void StructureElementCanvas::paintEvent(QPaintEvent *e){
    double interval = (double)widgetSize / size;
    painter->begin(this);

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->fillRect(0, 0, widgetSize, widgetSize, Qt::white);
    painter->drawRect(0, 0, widgetSize - 1, widgetSize - 1);
    int x;
    for(int i = 1; i < size; i++){
        x = i * interval;
        painter->drawLine(x, 0, x, widgetSize);
        painter->drawLine(0, x, widgetSize, x);
    }

    QRect rect;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(map[i][j] == 1){
                rect = QRect(i * interval, j * interval, interval + 1, interval + 1);
                painter->fillRect(rect, Qt::black);
            }
        }
    }

    QPainterPath path;
    path.addEllipse((anchor.x() + 0.5) * interval - 5,
                    (anchor.y() + 0.5) * interval - 5, 10, 10);
    path.setFillRule(Qt::WindingFill);
    painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(Qt::red);
    painter->drawPath(path);

    if(!enabled){
        painter->fillRect(0, 0, widgetSize, widgetSize, QColor(0, 0, 0, 100));
    }

    painter->end();
}

void StructureElementCanvas::setEnabled(bool e){
    enabled = e;
    update();
}

void StructureElementCanvas::sizeChange(int s){
    size = s;
    anchor = QPoint(s/2, s/2);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            map[i][j] = 1;
        }
    }
    update();
}

void StructureElementCanvas::getElementArray(QJsonArray &array){
    for(int j = 0; j < size; j++){
        for(int i = 0; i < size; i++){
            array.append(map[i][j]);
        }
    }
}

void StructureElementCanvas::getAnchor(int &x, int &y){
    x = anchor.x();
    y = anchor.y();
}
