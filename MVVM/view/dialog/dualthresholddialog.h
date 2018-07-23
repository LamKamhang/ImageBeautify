#ifndef DUALTHRESHOLDDIALOG_H
#define DUALTHRESHOLDDIALOG_H
#include <QWidget>
#include <QDialog>
#include "../common/parameters.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QSlider;
QT_END_NAMESPACE

class DualThresholdDialog
    : public QDialog
{
    Q_OBJECT

public:
    DualThresholdDialog(QWidget *parent, std::shared_ptr<QImage> image);


    void setImage(std::shared_ptr<QImage> image);

private slots:
    void update();

    void lowThresholdEditChanged(QString);
    void highThresholdEditChanged(QString);
    void lowThresholdSliderChanged(int);
    void highThresholdSliderChanged(int);
    void apply();

signals:
    void sendApplyDualThreshold(std::shared_ptr<JsonParameters>);

private:
    std::shared_ptr<QImage> image;
    QLabel *imageLabel;
    QLineEdit *lowThresholdEdit;
    QLineEdit *highThresholdEdit;
    QSlider *lowThresholdSlider;
    QSlider *highThresholdSlider;

};

#endif // DUALTHRESHOLDDIALOG_H
