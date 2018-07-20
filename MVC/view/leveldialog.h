#ifndef LEVELDIALOG_H
#define LEVELDIALOG_H

#include <QWidget>
#include <QDialog>
#include "../model/imageoperations.h"
QT_BEGIN_NAMESPACE
class QImage;
class QSlider;
class QLineEdit;
class QComboBox;
class QLabel;
QT_END_NAMESPACE

class LevelDialog : public QDialog
{
    Q_OBJECT

public:
    LevelDialog(QImage img);

signals:
    void sendApplyLevelAdjust(QImage);

private slots:
    void apply();
    void channelChanged(int);
    void shadowSliderChanged();
    void shadowSliderChanged(int);
    void midtonesSliderChanged();
    void midtonesSliderChanged(int);
    void highlightSliderChanged();
    void highlightSliderChanged(int);
    void outShadowSliderChanged();
    void outShadowSliderChanged(int);
    void outHighlightSliderChanged();
    void outHighlightSliderChanged(int);

private:
    ImageOperations *imageOp;
    QImage srcImage;
    QImage viewImage;
    QComboBox *channelBox;
    ColorLevelData data;
    PColorLevelItem currentItem;
    QSlider *shadowSlider;
    QSlider *midtonesSlider;
    QSlider *highlightSlider;
    QSlider *outShadowSlider;
    QSlider *outHighlightSlider;
    QLabel *imageLabel;
    QLabel *shadowValue;
    QLabel *midtonesValue;
    QLabel *highlightValue;
    QLabel *outShadowValue;
    QLabel *outHighlightValue;

    void updateImage(QImage &newImage);
    void updateView();
};

#endif // LEVELDIALOG_H
