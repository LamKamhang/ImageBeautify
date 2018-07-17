#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H

#include <QWidget>
#include <QDialog>
#include "histogramview.h"
#include "../model/imageoperations.h"

class HistogramDialog : public QDialog
{
    Q_OBJECT
public:
    HistogramDialog(QImage);

signals:
    void sendApplyHistogramEqualization(QImage);

private slots:
    void histogramEqualize();

private:
    QImage image;
    int *histogram;
    ImageOperations *imageOp;
    HistogramView *view;
};

#endif // HISTOGRAMDIALOG_H
