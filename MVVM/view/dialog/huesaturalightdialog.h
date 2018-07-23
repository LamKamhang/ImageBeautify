#ifndef HUESATURALIGHTDIALOG_H
#define HUESATURALIGHTDIALOG_H

#include <QWidget>
#include <QDialog>
#include "../../common/parameters.h"
QT_BEGIN_NAMESPACE
class QImage;
class QLineEdit;
class QComboBox;
class QSlider;
class QLabel;
QT_END_NAMESPACE

class HueSaturaLightDialog
    : public QDialog
{
    Q_OBJECT

public:
    enum TargetColorType{WHOLE_IMAGE = 0, RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};

    HueSaturaLightDialog(QWidget *parent, std::shared_ptr<QImage> img);
    void setImage(std::shared_ptr<QImage> img);

signals:
    void sendApplyHSLAdjust(std::shared_ptr<JsonParameters>);

private slots:
    void update();

    void hueEditChanged();
    void saturationEditChanged();
    void lightnessEditChanged();
    void hueSliderChanged();
    void saturationSliderChanged();
    void lightnessSliderChanged();
    void hueSliderChanged(int);
    void saturationSliderChanged(int);
    void lightnessSliderChanged(int);
    void targetColorChanged(int);
    void apply();

private:
    std::shared_ptr<QImage> image;
    QVector<int> hueValues;
    QLabel *imageLabel;
    QLineEdit *hueEdit;
    QLineEdit *saturationEdit;
    QLineEdit *lightnessEdit;
    QSlider *hueSlider;
    QSlider *saturationSlider;
    QSlider *lightnessSlider;
    QComboBox *hueTargetColor;
};

#endif // HUESATURALIGHTDIALOG_H
