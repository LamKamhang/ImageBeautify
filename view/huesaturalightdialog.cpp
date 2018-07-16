#include "huesaturalightdialog.h"
#include <QtWidgets>

HueSaturaLightDialog::HueSaturaLightDialog(QWidget *parent, QImage src)
    :QDialog(parent)
    ,img(src)
    ,srcImg(src)
    ,imageOperation(new ImageOperations)
{
    hueValues = QVector<int>(7, 0);

    QLabel *targetLabel = new QLabel;
    targetLabel->setText("Target");
    hueTargetColor = new QComboBox;
    hueTargetColor->addItem(tr("Whole Image"));
    hueTargetColor->addItem(tr("Red"));
    hueTargetColor->addItem(tr("Yellow"));
    hueTargetColor->addItem(tr("Green"));
    hueTargetColor->addItem(tr("Cyan"));
    hueTargetColor->addItem(tr("Blue"));
    hueTargetColor->addItem(tr("Magenta"));

    QHBoxLayout *hueTargetLayout = new QHBoxLayout;
    hueTargetLayout->addWidget(targetLabel);
    hueTargetLayout->addWidget(hueTargetColor);

    QLabel *hueLabel = new QLabel;
    hueLabel->setText("Hue: ");
    hueEdit = new QLineEdit;
    hueEdit->setText("+0");
    hueEdit->setMaximumWidth(50);

    QHBoxLayout *hueEditLayout = new QHBoxLayout;
    hueEditLayout->addWidget(hueLabel);
    hueEditLayout->addWidget(hueEdit);

    hueSlider = new QSlider(Qt::Horizontal);
    hueSlider->setMinimum(-180);
    hueSlider->setMaximum(180);
    hueSlider->setValue(0);

    QVBoxLayout *hueLayout = new QVBoxLayout;
    hueLayout->addLayout(hueTargetLayout);
    hueLayout->addLayout(hueEditLayout);
    hueLayout->addWidget(hueSlider);
    hueLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *hueGroup = new QGroupBox(tr("Hue Setting"));
    hueGroup->setLayout(hueLayout);

    QLabel *saturationLabel = new QLabel;
    saturationLabel->setText("Saturation: ");
    saturationEdit = new QLineEdit;
    saturationEdit->setText("+0");
    saturationEdit->setMaximumWidth(50);

    QHBoxLayout *saturationEditLayout = new QHBoxLayout;
    saturationEditLayout->addWidget(saturationLabel);
    saturationEditLayout->addWidget(saturationEdit);

    saturationSlider = new QSlider(Qt::Horizontal);
    saturationSlider->setMinimum(-100);
    saturationSlider->setMaximum(100);
    saturationSlider->setValue(0);

    QVBoxLayout *saturationLayout = new QVBoxLayout;
    saturationLayout->addLayout(saturationEditLayout);
    saturationLayout->addWidget(saturationSlider);
    saturationLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *saturationGroup = new QGroupBox(tr("Saturation Setting"));
    saturationGroup->setLayout(saturationLayout);

    QLabel *lightnessLabel = new QLabel;
    lightnessLabel->setText("Lightness: ");
    lightnessEdit = new QLineEdit;
    lightnessEdit->setText("+0");
    lightnessEdit->setMaximumWidth(50);

    QHBoxLayout *lightnessEditLayout = new QHBoxLayout;
    lightnessEditLayout->addWidget(lightnessLabel);
    lightnessEditLayout->addWidget(lightnessEdit);

    lightnessSlider = new QSlider(Qt::Horizontal);
    lightnessSlider->setMinimum(-100);
    lightnessSlider->setMaximum(100);
    lightnessSlider->setValue(0);

    QVBoxLayout *lightnessLayout = new QVBoxLayout;
    lightnessLayout->addLayout(lightnessEditLayout);
    lightnessLayout->addWidget(lightnessSlider);
    lightnessLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *lightnessGroup = new QGroupBox(tr("Lightness Setting"));
    lightnessGroup->setLayout(lightnessLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QIntValidator *hueValidator = new QIntValidator;
    hueValidator->setRange(-180, 180);
    hueEdit->setValidator(hueValidator);
    QIntValidator *slValidator = new QIntValidator;
    slValidator->setRange(-100, 100);
    saturationEdit->setValidator(slValidator);
    lightnessEdit->setValidator(slValidator);

    QVBoxLayout *settingLayout = new QVBoxLayout;
    settingLayout->addWidget(hueGroup);
    settingLayout->addWidget(saturationGroup);
    settingLayout->addWidget(lightnessGroup);
    settingLayout->addStretch(1);
    settingLayout->addSpacing(12);
    settingLayout->addLayout(btnLayout);

    imageLabel = new QLabel;
    imageLabel->setMaximumWidth(500);
    QPixmap pix = QPixmap::fromImage(img);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(500, 500 * h / w, Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);

    QVBoxLayout *imageLayout = new QVBoxLayout;
    imageLayout->addWidget(imageLabel);
    imageLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *imageGroup = new QGroupBox(tr("View Image"));
    imageGroup->setLayout(imageLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(imageGroup);
    mainLayout->addLayout(settingLayout);
    setLayout(mainLayout);

    connect(hueTargetColor, SIGNAL(currentIndexChanged(int)), this, SLOT(targetColorChanged(int)));
    connect(hueEdit, SIGNAL(editingFinished()), this, SLOT(hueEditChanged()));
    connect(saturationEdit, SIGNAL(editingFinished()), this, SLOT(saturationEditChanged()));
    connect(lightnessEdit, SIGNAL(editingFinished()), this, SLOT(lightnessEditChanged()));
    connect(hueSlider, SIGNAL(sliderReleased()), this, SLOT(hueSliderChanged()));
    connect(saturationSlider, SIGNAL(sliderReleased()), this, SLOT(saturationSliderChanged()));
    connect(lightnessSlider, SIGNAL(sliderReleased()), this, SLOT(lightnessSliderChanged()));
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &HueSaturaLightDialog::apply);

    setWindowTitle(tr("Adjust Hue/Saturation/Lightness Dialog"));
}

void HueSaturaLightDialog::targetColorChanged(int index){
    int val = hueValues[index];
    hueSlider->setValue(val);
    QString str;
    if(val >= 0){
        str = "+";
    }
    str += QString::number(val);
    hueEdit->setText(str);
}

void HueSaturaLightDialog::hueEditChanged(){
    QString str = hueEdit->text();
    int num = str.toInt();
    hueSlider->setValue(num);
    hueValues[hueTargetColor->currentIndex()] = num;
    QImage newImage = imageOperation->adjustHue(srcImg, img, hueValues);
    updateImage(newImage);
}

void HueSaturaLightDialog::saturationEditChanged(){
    QString str = saturationEdit->text();
    int num = str.toInt();
    saturationSlider->setValue(num);
    QImage newImage = imageOperation->adjustSaturation(srcImg, img, num);
    updateImage(newImage);
}

void HueSaturaLightDialog::lightnessEditChanged(){
    QString str = lightnessEdit->text();
    int num = str.toInt();
    lightnessSlider->setValue(num);
    QImage newImage = imageOperation->adjustLightness(srcImg, img, num);
    updateImage(newImage);
}

void HueSaturaLightDialog::hueSliderChanged(){
    int value = hueSlider->value();
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    hueEdit->setText(str);
    hueValues[hueTargetColor->currentIndex()] = value;
    QImage newImage = imageOperation->adjustHue(srcImg, img, hueValues);
    updateImage(newImage);
}

void HueSaturaLightDialog::saturationSliderChanged(){
    int value = saturationSlider->value();
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    saturationEdit->setText(str);
    QImage newImage = imageOperation->adjustLightness(srcImg, img, value);
    updateImage(newImage);
}

void HueSaturaLightDialog::lightnessSliderChanged(){
    int value = lightnessSlider->value();
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    lightnessEdit->setText(str);
    QImage newImage = imageOperation->adjustLightness(srcImg, img, value);
    updateImage(newImage);
}

void HueSaturaLightDialog::apply(){
    QJsonObject obj;
    QString saturation = saturationEdit->text();
    QString lightness = lightnessEdit->text();
    QJsonArray array;
    for(int i = 0; i < 7; i++){
        array.push_back(hueValues[i]);
    }
    obj.insert("hueValues", array);
    obj.insert("saturation", saturation);
    obj.insert("lightness", lightness);
    emit sendApplyHSLAdjust(obj, img);
    close();
}

void HueSaturaLightDialog::updateImage(QImage &newImage){
    img = newImage;
    QPixmap pix = QPixmap::fromImage(img);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(500, 500 * h / w, Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);
}
