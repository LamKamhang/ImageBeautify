#include "leveldialog.h"
#include <QtWidgets>

LevelDialog::LevelDialog(std::shared_ptr<QImage> img)
{
    setImage(img);
    data.Blue.Highlight = 255;
    data.Green.Highlight = 255;
    data.Red.Highlight = 255;
    data.RGB.Highlight = 255;
    data.Blue.Midtones = 1;
    data.Green.Midtones = 1;
    data.Red.Midtones = 1;
    data.RGB.Midtones = 1;
    data.Blue.OutHighlight = 255;
    data.Green.OutHighlight = 255;
    data.Red.OutHighlight = 255;
    data.RGB.OutHighlight = 255;
    data.Blue.OutShadow = 0;
    data.Green.OutShadow = 0;
    data.Red.OutShadow = 0;
    data.RGB.OutShadow = 0;
    data.Blue.Shadow = 0;
    data.Green.Shadow = 0;
    data.Red.Shadow = 0;
    data.RGB.Shadow = 0;

    currentItem = &data.Red;

    QLabel *channelLabel = new QLabel;
    channelLabel->setText(tr("Channel:"));
    channelBox = new QComboBox;
    channelBox->addItem(tr("Red"));
    channelBox->addItem(tr("Green"));
    channelBox->addItem(tr("Blue"));
    channelBox->addItem(tr("RGB"));

    QHBoxLayout *channelLayout = new QHBoxLayout;
    channelLayout->addWidget(channelLabel);
    channelLayout->addWidget(channelBox);

    QGroupBox *channelGroup = new QGroupBox(tr("Channel"));
    channelGroup->setLayout(channelLayout);

    QLabel *shadowLabel = new QLabel;
    shadowLabel->setText(tr("Shadow: "));
    shadowValue = new QLabel;
    shadowValue->setText(tr("0"));
    shadowValue->setAlignment(Qt::AlignRight);

    QHBoxLayout *inShadowLabelLayout = new QHBoxLayout;
    inShadowLabelLayout->addWidget(shadowLabel);
    inShadowLabelLayout->addWidget(shadowValue);

    shadowSlider = new QSlider(Qt::Horizontal);
    shadowSlider->setMinimum(0);
    shadowSlider->setMaximum(255);
    shadowSlider->setValue(0);

    QVBoxLayout *inShadowLayout = new QVBoxLayout;
    inShadowLayout->addLayout(inShadowLabelLayout);
    inShadowLayout->addWidget(shadowSlider);
    inShadowLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *midtonesLabel = new QLabel;
    midtonesLabel->setText(tr("Midtones: "));
    midtonesValue = new QLabel;
    midtonesValue->setText(tr("1.0"));
    midtonesValue->setAlignment(Qt::AlignRight);

    QHBoxLayout *inMidtonesLabelLayout = new QHBoxLayout;
    inMidtonesLabelLayout->addWidget(midtonesLabel);
    inMidtonesLabelLayout->addWidget(midtonesValue);

    midtonesSlider = new QSlider(Qt::Horizontal);
    midtonesSlider->setMinimum(0);
    midtonesSlider->setMaximum(20);
    midtonesSlider->setValue(10);

    QVBoxLayout *inMidtonesLayout = new QVBoxLayout;
    inMidtonesLayout->addLayout(inMidtonesLabelLayout);
    inMidtonesLayout->addWidget(midtonesSlider);
    inMidtonesLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *highlightLabel = new QLabel;
    highlightLabel->setText(tr("Highlight: "));
    highlightValue = new QLabel;
    highlightValue->setText(tr("255"));
    highlightValue->setAlignment(Qt::AlignRight);

    QHBoxLayout *inHighlightLabelLayout = new QHBoxLayout;
    inHighlightLabelLayout->addWidget(highlightLabel);
    inHighlightLabelLayout->addWidget(highlightValue);

    highlightSlider = new QSlider(Qt::Horizontal);
    highlightSlider->setMinimum(0);
    highlightSlider->setMaximum(255);
    highlightSlider->setValue(255);

    QVBoxLayout *inHighlightLayout = new QVBoxLayout;
    inHighlightLayout->addLayout(inHighlightLabelLayout);
    inHighlightLayout->addWidget(highlightSlider);
    inHighlightLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *inLayout = new QVBoxLayout;
    inLayout->addLayout(inShadowLayout);
    inLayout->addLayout(inMidtonesLayout);
    inLayout->addLayout(inHighlightLayout);

    QGroupBox *inGroup = new QGroupBox(tr("In Level"));
    inGroup->setLayout(inLayout);

    QLabel *outShadowLabel = new QLabel;
    outShadowLabel->setText(tr("Shadow: "));
    outShadowValue = new QLabel;
    outShadowValue->setText(tr("0"));
    outShadowValue->setAlignment(Qt::AlignRight);

    QHBoxLayout *outShadowLabelLayout = new QHBoxLayout;
    outShadowLabelLayout->addWidget(outShadowLabel);
    outShadowLabelLayout->addWidget(outShadowValue);

    outShadowSlider = new QSlider(Qt::Horizontal);
    outShadowSlider->setMinimum(0);
    outShadowSlider->setMaximum(255);
    outShadowSlider->setValue(0);

    QVBoxLayout *outShadowLayout = new QVBoxLayout;
    outShadowLayout->addLayout(outShadowLabelLayout);
    outShadowLayout->addWidget(outShadowSlider);
    outShadowLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *outHighlightLabel = new QLabel;
    outHighlightLabel->setText(tr("Highlight: "));
    outHighlightValue = new QLabel;
    outHighlightValue->setText(tr("255"));
    outHighlightValue->setAlignment(Qt::AlignRight);

    QHBoxLayout *outHighlightLabelLayout = new QHBoxLayout;
    outHighlightLabelLayout->addWidget(outHighlightLabel);
    outHighlightLabelLayout->addWidget(outHighlightValue);

    outHighlightSlider = new QSlider(Qt::Horizontal);
    outHighlightSlider->setMinimum(0);
    outHighlightSlider->setMaximum(255);
    outHighlightSlider->setValue(255);

    QVBoxLayout *outHighlightLayout = new QVBoxLayout;
    outHighlightLayout->addLayout(outHighlightLabelLayout);
    outHighlightLayout->addWidget(outHighlightSlider);
    outHighlightLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *outLayout = new QVBoxLayout;
    outLayout->addLayout(outShadowLayout);
    outLayout->addLayout(outHighlightLayout);

    QGroupBox *outGroup = new QGroupBox(tr("Out Level"));
    outGroup->setLayout(outLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *settingLayout = new QVBoxLayout;
    settingLayout->addWidget(channelGroup);
    settingLayout->addWidget(inGroup);
    settingLayout->addWidget(outGroup);
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

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &LevelDialog::apply);
    connect(channelBox, SIGNAL(currentIndexChanged(int)), this, SLOT(channelChanged(int)));
    connect(shadowSlider, SIGNAL(sliderReleased()), this, SLOT(shadowSliderChanged()));
    connect(shadowSlider, SIGNAL(sliderMoved(int)), this, SLOT(shadowSliderChanged(int)));
    connect(midtonesSlider, SIGNAL(sliderReleased()), this, SLOT(midtonesSliderChanged()));
    connect(midtonesSlider, SIGNAL(sliderMoved(int)), this, SLOT(midtonesSliderChanged(int)));
    connect(highlightSlider, SIGNAL(sliderReleased()), this, SLOT(highlightSliderChanged()));
    connect(highlightSlider, SIGNAL(sliderMoved(int)), this, SLOT(highlightSliderChanged(int)));
    connect(outShadowSlider, SIGNAL(sliderReleased()), this, SLOT(outShadowSliderChanged()));
    connect(outShadowSlider, SIGNAL(sliderMoved(int)), this, SLOT(outShadowSliderChanged(int)));
    connect(outHighlightSlider, SIGNAL(sliderReleased()), this, SLOT(outHighlightSliderChanged()));
    connect(outHighlightSlider, SIGNAL(sliderMoved(int)), this, SLOT(outHighlightSliderChanged(int)));
}

void LevelDialog::apply(){
    sendData(true);
    close();
}

void LevelDialog::channelChanged(int index){
    switch(index){
    case 0:
        currentItem = &data.Red;
        break;
    case 1:
        currentItem = &data.Green;
        break;
    case 2:
        currentItem = &data.Blue;
        break;
    case 3:
        currentItem = &data.RGB;
        break;
    default:
        break;
    }
    shadowSlider->setValue(currentItem->Shadow);
    shadowValue->setText(QString::number(currentItem->Shadow));
    midtonesSlider->setValue(10 * currentItem->Midtones);
    midtonesValue->setText(QString::number(currentItem->Midtones));
    highlightSlider->setValue(currentItem->Highlight);
    highlightValue->setText(QString::number(currentItem->Highlight));
    outShadowSlider->setValue(currentItem->OutShadow);
    outShadowValue->setText(QString::number(currentItem->OutShadow));
    outHighlightSlider->setValue(currentItem->OutHighlight);
    outHighlightValue->setText(QString::number(currentItem->OutHighlight));
}

void LevelDialog::shadowSliderChanged(){
    int value = shadowSlider->value();
    shadowValue->setText(QString::number(value));
    currentItem->Shadow = value;
    sendData(false);
}

void LevelDialog::shadowSliderChanged(int value){
    shadowValue->setText(QString::number(value));
    currentItem->Shadow = value;
    sendData(false);
}

void LevelDialog::midtonesSliderChanged(){
    int value = midtonesSlider->value();
    float realVal = value / 10.0;
    midtonesValue->setText(QString::number(realVal));
    currentItem->Midtones = realVal;
    sendData(false);
}

void LevelDialog::midtonesSliderChanged(int value){
    float realVal = value / 10.0;
    midtonesValue->setText(QString::number(realVal));
    currentItem->Midtones = realVal;
    sendData(false);
}

void LevelDialog::highlightSliderChanged(){
    int value = highlightSlider->value();
    highlightValue->setText(QString::number(value));
    currentItem->Highlight = value;
    sendData(false);
}

void LevelDialog::highlightSliderChanged(int value){
    highlightValue->setText(QString::number(value));
    currentItem->Highlight = value;
    sendData(false);
}

void LevelDialog::outShadowSliderChanged(){
    int value = outShadowSlider->value();
    outShadowValue->setText(QString::number(value));
    currentItem->OutShadow = value;
    sendData(false);
}

void LevelDialog::outShadowSliderChanged(int value){
    outShadowValue->setText(QString::number(value));
    currentItem->OutShadow = value;
    sendData(false);
}

void LevelDialog::outHighlightSliderChanged(){
    int value = outHighlightSlider->value();
    outHighlightValue->setText(QString::number(value));
    currentItem->OutHighlight = value;
    sendData(false);
}

void LevelDialog::outHighlightSliderChanged(int value){
    outHighlightValue->setText(QString::number(value));
    currentItem->OutHighlight = value;
    sendData(false);
}

void LevelDialog::sendData(bool apply){
    JsonParameters json;
    json.insert("apply",std::make_shared<BoolParameters>(apply));
    json.insert("data",std::make_shared<ColorLevelDataParameters>(data));
    emit sendApplyLevelAdjust(std::make_shared<JsonParameters>(json));
}

void LevelDialog::setImage(std::shared_ptr<QImage> img){
    image = img;
}

void LevelDialog::update(){
    QPixmap pix = QPixmap::fromImage(*image);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(500, 500 * h / w, Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);
}

