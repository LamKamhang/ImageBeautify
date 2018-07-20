#include "houghtransformdialog.h"
#include <QtWidgets>

HoughTransformDialog::HoughTransformDialog()
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
    connect(applyButton, &QAbstractButton::clicked, this, &HoughTransformDialog::apply);

    setWindowTitle(tr("Hough Transformation Dialog"));
    setMinimumWidth(500);
}

void HoughTransformDialog::apply(){
    QJsonObject obj;
    int lo = loRadiusEdit->text().toInt();
    int hi = hiRadiusEdit->text().toInt();
    if(lo > hi){
        QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
                           tr("Low radius should be smaller than high radius."));
        msgBox.exec();
        return;
    }
    obj.insert("lo", lo);
    obj.insert("hi", hi);
    emit sendApplyHoughTransform(obj);
    close();
}
