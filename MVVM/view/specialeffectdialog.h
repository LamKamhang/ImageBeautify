#ifndef SPECIALEFFECTDIALOG_H
#define SPECIALEFFECTDIALOG_H
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include "clickableqlabel.h"
#include "../common/parameters.h"

class SpecialEffectDialog : public QDialog
{
    Q_OBJECT
public:
    SpecialEffectDialog(std::shared_ptr<QImage> img);
    void setImage(std::shared_ptr<QImage> img);

signals:
    void sendApplySpecialEffect(std::shared_ptr<JsonParameters> json);

private slots:
    void update();

    void apply();
    void handlespecialeffects1();
    void handlespecialeffects2();
    void handlespecialeffects3();
    void handlespecialeffects4();
    void handlespecialeffects5();
    void handlespecialeffects6();
    void handlespecialeffects7();
    void handlespecialeffects8();
    void handlespecialeffects9();
    void handlespecialeffects10();
    void handlespecialeffects11();
    void handlespecialeffects12();
    void handlespecialeffects13();
    void handlealphaslider();
    void handlealphaslider(int);

private:
    void sendData(bool apply);

    const int imageMaxHeight = 660;
    const int imageMaxWidth = 900;

    std::shared_ptr<QImage> image;
    enum EffectsType effectsType;
    QSlider *alphaSlider;
    QLabel *alphaValue;
    QLabel *imageLabel;
};

#endif // SPECIALEFFECTDIALOG_H
