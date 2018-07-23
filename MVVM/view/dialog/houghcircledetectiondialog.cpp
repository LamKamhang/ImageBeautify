#include "houghcircledetectiondialog.h"
#include <QWidget>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleValidator>
#include <QMessageBox>
#include <QButtonGroup>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>

HoughCircleDetectionDialog::HoughCircleDetectionDialog()
{
    QLabel *fromLabel = new QLabel;
    fromLabel->setText("From: ");
    loRadiusEdit = new QLineEdit;
    loRadiusEdit->setText("10");
    loRadiusEdit->setMaximumWidth(50);

    QHBoxLayout *loLayout = new QHBoxLayout;
    loLayout->addWidget(fromLabel);
    loLayout->addWidget(loRadiusEdit);
    loLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *toLabel = new QLabel;
    toLabel->setText("To: ");
    hiRadiusEdit = new QLineEdit;
    hiRadiusEdit->setText("20");
    hiRadiusEdit->setMaximumWidth(50);

    QHBoxLayout *hiLayout = new QHBoxLayout;
    hiLayout->addWidget(toLabel);
    hiLayout->addWidget(hiRadiusEdit);
    hiLayout->setContentsMargins(10, 10, 10, 10);

    QIntValidator *validator = new QIntValidator;
    validator->setRange(0, 500);
    loRadiusEdit->setValidator(validator);
    hiRadiusEdit->setValidator(validator);

    QVBoxLayout *radiusLayout = new QVBoxLayout;
    radiusLayout->addLayout(loLayout);
    radiusLayout->addLayout(hiLayout);

    QGroupBox *radiusGroup = new QGroupBox(tr("Radius Setting"));
    radiusGroup->setLayout(radiusLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(radiusGroup);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &HoughCircleDetectionDialog::apply);

    setWindowTitle(tr("Hough Circle Detection Dialog"));
    setMinimumWidth(500);
}

void HoughCircleDetectionDialog::apply(){
    JsonParameters obj;
    int lo = loRadiusEdit->text().toInt();
    int hi = hiRadiusEdit->text().toInt();
    if(lo > hi){
        QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
                           tr("Low radius should be smaller than high radius."));
        msgBox.exec();
        return;
    }
    obj.insert("lo", std::make_shared<IntParameters>(lo));
    obj.insert("hi", std::make_shared<IntParameters>(hi));
    emit sendApplyHoughCircleDetection(std::make_shared<JsonParameters>(obj));
    close();
}

