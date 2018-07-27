#include "histogramview.h"
#include <QtWidgets>
#include <iostream>

HistogramView::HistogramView(int *histo, int w, int h, QWidget *parent)
    : QWidget(parent)
    , width(w)
    , height(h)
    , histogram(new int[256])
{
    this->setFixedSize(w, h);
    maxPix = 0;
    for(int i = 0; i < 256; i++){
        if(histo[i] > maxPix){
            maxPix = histo[i];
            maxX = i;
        }
    }
    for(int i = 0; i < 256; i++){
        histogram[i] = histo[i] * h / maxPix;
    }
    update();
}

void HistogramView::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);
    painter.fillRect(0, 0, width, height, Qt::white);
    for(int i = 0; i < 256; i++){
        painter.fillRect(i * width / 256, height - histogram[i], width / 256, histogram[i], Qt::black);
    }
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawText(QPoint(0,0),QString::number(maxPix));
    painter.drawText(QRect(0,0,this->width, this->height/4),Qt::AlignCenter,
                     tr("Max pixel gray degree: %1").arg(maxX));
    painter.end();
}
