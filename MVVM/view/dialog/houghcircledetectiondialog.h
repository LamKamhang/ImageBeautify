#ifndef HOUGHCIRCLEDETECTIONDIALOG_H
#define HOUGHCIRCLEDETECTIONDIALOG_H

#include <QWidget>
#include <QDialog>
#include "../../common/parameters.h"
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class HoughCircleDetectionDialog
    : public QDialog
{
    Q_OBJECT

public:
    HoughCircleDetectionDialog();

signals:
    void sendApplyHoughCircleDetection(std::shared_ptr<JsonParameters> json);

private slots:
    void apply();

private:
    QLineEdit *loRadiusEdit;
    QLineEdit *hiRadiusEdit;

};

#endif // HOUGHCIRCLEDETECTIONDIALOG_H
