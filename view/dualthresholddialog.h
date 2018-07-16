#ifndef DUALTHRESHOLDDIALOG_H
#define DUALTHRESHOLDDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QJsonObject>
#include "../model/imageoperations.h"
QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QSlider;
QT_END_NAMESPACE

class DualThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    DualThresholdDialog(QWidget *parent, QImage src);

private slots:
    void lowThresholdEditChanged(QString);
    void highThresholdEditChanged(QString);
    void lowThresholdSliderChanged(int);
    void highThresholdSliderChanged(int);
    void apply();

signals:
    void sendApplyDualThreshold(QJsonObject, QImage);

private:
    ImageOperations *imageOperation;
    QImage image;
    QImage srcImg;
    QLabel *imageLabel;
    QLineEdit *lowThresholdEdit;
    QLineEdit *highThresholdEdit;
    QSlider *lowThresholdSlider;
    QSlider *highThresholdSlider;

    void updateImage(QImage &newImage);
};

#endif // DUALTHRESHOLDDIALOG_H
