#ifndef CURVEDIALOG_H
#define CURVEDIALOG_H
#include <QWidget>
#include <QDialog>
#include "../../common/parameters.h"
#include "curvecanvas.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QLabel;
class QButtonGroup;
QT_END_NAMESPACE

class CurveDialog : public QDialog
{
    Q_OBJECT
public:
    CurveDialog(std::shared_ptr<QImage> img);

    void setImage(std::shared_ptr<QImage> img);

signals:
    void sendApplyCurve(std::shared_ptr<JsonParameters>);

private slots:
    void update();

    void apply();
    void curveTypeChanged(int);
    void linearCurveChange(QPoint p1, QPoint p2);
    void pieceLinCurveChange(QPoint p1, QPoint p2);
    void logCurveChange(double a, double b);
    void expCurveChange(double a, double b);

private:
    CurveCanvas *canvas;
    double m_a,m_b;
    QPoint m_p1,m_p2;
    std::shared_ptr<QImage> image;
    QLabel *imageLabel;
    QButtonGroup *btnGroup;
};

#endif // CURVEDIALOG_H
