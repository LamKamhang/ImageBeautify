#ifndef CURVEDIALOG_H
#define CURVEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QJsonObject>
#include "curvecanvas.h"
#include "../model/imageoperations.h"
QT_BEGIN_NAMESPACE
class QLineEdit;
class QLabel;
class QButtonGroup;
QT_END_NAMESPACE

class CurveDialog : public QDialog
{
    Q_OBJECT

public:
    CurveDialog(QImage img);

signals:
    void sendApplyCurve(QJsonObject, QImage);

private slots:
    void apply();
    void curveTypeChanged(int);
    void linearCurveChange(QPoint p1, QPoint p2);
    void pieceLinCurveChange(QPoint p1, QPoint p2);
    void logCurveChange(double a, double b);
    void expCurveChange(double a, double b);

private:
    ImageOperations *imageOp;
    CurveCanvas *canvas;
    QImage srcImage;
    QImage viewImage;
    QLabel *imageLabel;
    QButtonGroup *btnGroup;

    void updateImage(QImage &newImage);
};

#endif // CURVEDIALOG_H
