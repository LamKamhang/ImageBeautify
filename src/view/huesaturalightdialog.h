#ifndef HUESATURALIGHTDIALOG_H
#define HUESATURALIGHTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QJsonObject>
#include "../model/imageoperations.h"
QT_BEGIN_NAMESPACE
class QImage;
class QLineEdit;
class QComboBox;
class QSlider;
class QLabel;
QT_END_NAMESPACE

class HueSaturaLightDialog : public QDialog
{
    Q_OBJECT

public:
    enum TargetColorType{WHOLE_IMAGE = 0, RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};

    HueSaturaLightDialog(QWidget *parent, QImage src);

signals:
    void sendApplyHSLAdjust(QJsonObject, QImage);

private slots:
    void hueEditChanged();
    void saturationEditChanged();
    void lightnessEditChanged();
    void hueSliderChanged();
    void saturationSliderChanged();
    void lightnessSliderChanged();
    void hueSliderChanged(int);
    void saturationSliderChanged(int);
    void lightnessSliderChanged(int);
    void apply();
    void targetColorChanged(int);

private:
    ImageOperations *imageOperation;
    QImage img;
    QImage srcImg;
    QVector<int> hueValues;
    QLabel *imageLabel;
    QLineEdit *hueEdit;
    QLineEdit *saturationEdit;
    QLineEdit *lightnessEdit;
    QSlider *hueSlider;
    QSlider *saturationSlider;
    QSlider *lightnessSlider;
    QComboBox *hueTargetColor;

    void updateImage(QImage &newImage);
};

#endif // HUESATURALIGHTDIALOG_H
