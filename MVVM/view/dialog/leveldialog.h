#ifndef LEVELDIALOG_H
#define LEVELDIALOG_H
#include <QWidget>
#include <QDialog>
#include "../../common/parameters.h"

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
    LevelDialog(std::shared_ptr<QImage> img);
    void setImage(std::shared_ptr<QImage> img);

signals:
    void sendApplyLevelAdjust(std::shared_ptr<JsonParameters>);

private slots:
    void update();

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
    void sendData(bool);

    std::shared_ptr<QImage> image;
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

};

#endif // LEVELDIALOG_H
