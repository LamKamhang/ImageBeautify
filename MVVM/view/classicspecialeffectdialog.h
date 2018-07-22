#ifndef CLASSICSPECIALEFFECTDIALOG_H
#define CLASSICSPECIALEFFECTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include "clickableqlabel.h"
#include "../common/parameters.h"

class ClassicSpecialEffectDialog : public QDialog
{
    Q_OBJECT
public:
    ClassicSpecialEffectDialog(std::shared_ptr<QImage> img);
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
    void handlealphaslider();
    void handlealphaslider(int);

private:
    void sendData(bool apply);
    QPixmap Icon2Pixmap(QImage icon);

    const int imageMaxHeight = 660;
    const int imageMaxWidth = 900;
    const int seGroupMinWidth = 120;
    const int seGroupMinHeight = 150;

    std::shared_ptr<QImage> image;
    enum EffectsType effectsType;
    QSlider *alphaSlider;
    QLabel *alphaValue;
    QLabel *imageLabel;
};

#endif // CLASSICSPECIALEFFECTDIALOG_H
