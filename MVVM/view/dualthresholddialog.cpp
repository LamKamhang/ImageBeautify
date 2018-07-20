#include "dualthresholddialog.h"
#include <QtWidgets>

DualThresholdDialog::DualThresholdDialog(QWidget *parent, std::shared_ptr<QImage> img)
    : QDialog(parent)
{
    setImage(img);
    imageLabel = new QLabel;
    imageLabel->setMaximumWidth(500);
    update();

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

void DualThresholdDialog::setImage(std::shared_ptr<QImage> image){
    this->image = image;
}

void DualThresholdDialog::lowThresholdEditChanged(QString str){
    JsonParameters obj;
    bool apply = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    int lo = str.toInt();
    lowThresholdSlider->setValue(lo);
    int hi = highThresholdSlider->value();
    obj.insert("low", std::make_shared<IntParameters>(lo));
    obj.insert("high", std::make_shared<IntParameters>(hi));
    emit sendApplyDualThreshold(std::make_shared<JsonParameters>(obj));
}

void DualThresholdDialog::highThresholdEditChanged(QString str){
    JsonParameters obj;
    bool apply = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    int hi = str.toInt();
    highThresholdSlider->setValue(hi);
    int lo = lowThresholdSlider->value();
    obj.insert("low", std::make_shared<IntParameters>(lo));
    obj.insert("high", std::make_shared<IntParameters>(hi));
    emit sendApplyDualThreshold(std::make_shared<JsonParameters>(obj));
}

void DualThresholdDialog::lowThresholdSliderChanged(int value){
    JsonParameters obj;
    bool apply = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    int hi = highThresholdSlider->value();
    int lo = value;
    lowThresholdEdit->setText(QString::number(lo));
    obj.insert("low", std::make_shared<IntParameters>(lo));
    obj.insert("high", std::make_shared<IntParameters>(hi));
    emit sendApplyDualThreshold(std::make_shared<JsonParameters>(obj));
}

void DualThresholdDialog::highThresholdSliderChanged(int value){
    JsonParameters obj;
    bool apply = false;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    int hi = value;
    highThresholdEdit->setText(QString::number(hi));
    int lo = lowThresholdSlider->value();
    obj.insert("low", std::make_shared<IntParameters>(lo));
    obj.insert("high", std::make_shared<IntParameters>(hi));
    emit sendApplyDualThreshold(std::make_shared<JsonParameters>(obj));
}

void DualThresholdDialog::apply(){
    JsonParameters obj;
    bool apply = true;
    obj.insert("apply", std::make_shared<BoolParameters>(apply));
    obj.insert("low", std::make_shared<IntParameters>(lowThresholdSlider->value()));
    obj.insert("high", std::make_shared<IntParameters>(highThresholdSlider->value()));
    emit sendApplyDualThreshold(std::make_shared<JsonParameters>(obj));
    close();
}

void DualThresholdDialog::update(){
    QPixmap pix = QPixmap::fromImage(*image);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(500, 500 * h / w, Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);
}


