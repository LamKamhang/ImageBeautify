#include "dualthresholddialog.h"
#include <QtWidgets>

DualThresholdDialog::DualThresholdDialog(QWidget *parent, QImage src)
    :QDialog(parent)
    ,image(src)
    ,srcImg(src)
    ,imageOperation(new ImageOperations)
{
    imageLabel = new QLabel;
    imageLabel->setMaximumWidth(500);
    QPixmap pix = QPixmap::fromImage(image);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(500, 500 * h / w, Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);

    QVBoxLayout *imageLayout = new QVBoxLayout;
    imageLayout->addWidget(imageLabel);
    imageLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *imageGroup = new QGroupBox(tr("View Image"));
    imageGroup->setLayout(imageLayout);

    QLabel *lowThresholdLabel = new QLabel;
    lowThresholdLabel->setText(tr("Value: (from 0 to 255)"));
    lowThresholdEdit = new QLineEdit;
    lowThresholdEdit->setText("0");
    lowThresholdEdit->setMaximumWidth(50);

    QHBoxLayout *lowEditLayout = new QHBoxLayout;
    lowEditLayout->addWidget(lowThresholdLabel);
    lowEditLayout->addWidget(lowThresholdEdit);

    lowThresholdSlider = new QSlider(Qt::Horizontal);
    lowThresholdSlider->setMinimum(0);
    lowThresholdSlider->setMaximum(255);
    lowThresholdSlider->setValue(0);

    QVBoxLayout *lowLayout = new QVBoxLayout;
    lowLayout->addLayout(lowEditLayout);
    lowLayout->addWidget(lowThresholdSlider);
    lowLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *lowGroup = new QGroupBox(tr("Low Threshold"));
    lowGroup->setLayout(lowLayout);

    QLabel *highThresholdLabel = new QLabel;
    highThresholdLabel->setText(tr("Value: (from 0 to 255"));
    highThresholdEdit = new QLineEdit;
    highThresholdEdit->setText("0");
    highThresholdEdit->setMaximumWidth(50);

    QHBoxLayout *highEditLayout = new QHBoxLayout;
    highEditLayout->addWidget(highThresholdLabel);
    highEditLayout->addWidget(highThresholdEdit);

    highThresholdSlider = new QSlider(Qt::Horizontal);
    highThresholdSlider->setMinimum(0);
    highThresholdSlider->setMaximum(255);
    highThresholdSlider->setValue(0);

    QVBoxLayout *highLayout = new QVBoxLayout;
    highLayout->addLayout(highEditLayout);
    highLayout->addWidget(highThresholdSlider);
    highLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *highGroup = new QGroupBox(tr("High Threshold"));
    highGroup->setLayout(highLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QIntValidator *thresholdValidator = new QIntValidator;
    thresholdValidator->setRange(0, 255);
    lowThresholdEdit->setValidator(thresholdValidator);
    highThresholdEdit->setValidator(thresholdValidator);

    QVBoxLayout *settingLayout = new QVBoxLayout;
    settingLayout->addWidget(lowGroup);
    settingLayout->addWidget(highGroup);
    settingLayout->addStretch(1);
    settingLayout->addSpacing(12);
    settingLayout->addLayout(btnLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(imageGroup);
    mainLayout->addLayout(settingLayout);
    setLayout(mainLayout);

    connect(lowThresholdEdit, SIGNAL(textChanged(QString)), this, SLOT(lowThresholdEditChanged(QString)));
    connect(highThresholdEdit, SIGNAL(textChanged(QString)), this, SLOT(highThresholdEditChanged(QString)));
    connect(lowThresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(lowThresholdSliderChanged(int)));
    connect(highThresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(highThresholdSliderChanged(int)));
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &DualThresholdDialog::apply);
}

void DualThresholdDialog::lowThresholdEditChanged(QString str){
    int num = str.toInt();
    lowThresholdSlider->setValue(num);
    QImage newImage = imageOperation->dualThreshold(srcImg, num, highThresholdSlider->value());
    updateImage(newImage);
}

void DualThresholdDialog::highThresholdEditChanged(QString str){
    int num = str.toInt();
    highThresholdSlider->setValue(num);
    QImage newImage = imageOperation->dualThreshold(srcImg, lowThresholdSlider->value(), num);
    updateImage(newImage);
}

void DualThresholdDialog::lowThresholdSliderChanged(int value){
    lowThresholdEdit->setText(QString::number(value));
    QImage newImage = imageOperation->dualThreshold(srcImg, lowThresholdSlider->value(), highThresholdSlider->value());
    updateImage(newImage);
}

void DualThresholdDialog::highThresholdSliderChanged(int value){
    highThresholdEdit->setText(QString::number(value));
    QImage newImage = imageOperation->dualThreshold(srcImg, lowThresholdSlider->value(), highThresholdSlider->value());
    updateImage(newImage);
}

void DualThresholdDialog::apply(){
    QJsonObject obj;
    obj.insert("low", lowThresholdEdit->text());
    obj.insert("high", highThresholdEdit->text());
    emit sendApplyDualThreshold(obj, image);
    close();
}

void DualThresholdDialog::updateImage(QImage &newImage){
    image = newImage;
    QPixmap pix = QPixmap::fromImage(image);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(500, 500 * h / w, Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);
}
