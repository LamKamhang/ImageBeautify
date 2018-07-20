#include "huesaturalightdialog.h"
#include <QtWidgets>

HueSaturaLightDialog::HueSaturaLightDialog(QWidget *parent, std::shared_ptr<QImage> img)
    : QDialog(parent)
{
    setImage(img);
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
    update();

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

    connect(hueSlider, SIGNAL(sliderMoved(int)), this, SLOT(hueSliderChanged(int)));
    connect(saturationSlider, SIGNAL(sliderMoved(int)), this, SLOT(saturationSliderChanged(int)));
    connect(lightnessSlider, SIGNAL(sliderMoved(int)), this, SLOT(lightnessSliderChanged(int)));

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &HueSaturaLightDialog::apply);

    setWindowTitle(tr("Adjust Hue/Saturation/Lightness Dialog"));

}

void HueSaturaLightDialog::setImage(std::shared_ptr<QImage> img){
    image = img;
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
    JsonParameters obj;
    bool apply = false;
    bool hue = true;
    bool saturation = false;
    bool lightness = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    QString str = hueEdit->text();
    int num = str.toInt();
    hueSlider->setValue(num);
    hueValues[hueTargetColor->currentIndex()] = num;
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::saturationEditChanged(){
    JsonParameters obj;
    bool apply = false;
    bool hue = false;
    bool saturation = true;
    bool lightness = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    QString str = saturationEdit->text();
    int num = str.toInt();
    saturationSlider->setValue(num);
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::lightnessEditChanged(){
    JsonParameters obj;
    bool apply = false;
    bool hue = false;
    bool saturation = false;
    bool lightness = true;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    QString str = lightnessEdit->text();
    int num = str.toInt();
    lightnessSlider->setValue(num);
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::hueSliderChanged(){
    JsonParameters obj;
    bool apply = false;
    bool hue = true;
    bool saturation = false;
    bool lightness = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    int value = hueSlider->value();
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    hueEdit->setText(str);
    hueValues[hueTargetColor->currentIndex()] = value;
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::hueSliderChanged(int value){
    JsonParameters obj;
    bool apply = false;
    bool hue = true;
    bool saturation = false;
    bool lightness = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    hueEdit->setText(str);
    hueValues[hueTargetColor->currentIndex()] = value;
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::saturationSliderChanged(){
    JsonParameters obj;
    bool apply = false;
    bool hue = false;
    bool saturation = true;
    bool lightness = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    int value = saturationSlider->value();
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    saturationEdit->setText(str);
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::saturationSliderChanged(int value){
    JsonParameters obj;
    bool apply = false;
    bool hue = false;
    bool saturation = true;
    bool lightness = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    saturationEdit->setText(str);
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::lightnessSliderChanged(){
    JsonParameters obj;
    bool apply = false;
    bool hue = false;
    bool saturation = false;
    bool lightness = true;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    int value = lightnessSlider->value();
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    lightnessEdit->setText(str);
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::lightnessSliderChanged(int value){
    JsonParameters obj;
    bool apply = false;
    bool hue = false;
    bool saturation = false;
    bool lightness = true;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));
    QString str;
    if(value >= 0){
        str = "+";
    }
    str += QString::number(value);
    lightnessEdit->setText(str);
    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
}

void HueSaturaLightDialog::apply(){
    JsonParameters obj;
    bool apply = true;
    bool hue = false;
    bool saturation = false;
    bool lightness = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("hue", std::make_shared<BoolParameters>(hue));
    obj.insert("saturation", std::make_shared<BoolParameters>(saturation));
    obj.insert("lightness", std::make_shared<BoolParameters>(lightness));

    obj.insert("hueValues",std::make_shared<QVectorParameters<int>>(hueValues));
    obj.insert("saturationValue",std::make_shared<IntParameters>(saturationSlider->value()));
    obj.insert("lightnessValue",std::make_shared<IntParameters>(lightnessSlider->value()));
    emit sendApplyHSLAdjust(std::make_shared<JsonParameters>(obj));
    close();
}

void HueSaturaLightDialog::update(){
    QPixmap pix = QPixmap::fromImage(*image);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(500, 500 * h / w, Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);
}
