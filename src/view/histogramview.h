#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QWidget>
#include <QPaintEvent>

class HistogramView : public QWidget
{
    Q_OBJECT
public:
    HistogramView(int *histo, int w = 256, int h = 100, QWidget *parent = 0);

private:
    int *histogram;
    int width;
    int height;
    int maxPix;
    int maxX;
    void paintEvent(QPaintEvent *e);
};

#endif // HISTOGRAMVIEW_H
