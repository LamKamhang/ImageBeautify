#include "scaledialog.h"
#include <QtWidgets>

ScaleDialog::ScaleDialog()
{
    QRadioButton *nearnestBtn = new QRadioButton;
    nearnestBtn->setText("Nearnest Interpolation");
    nearnestBtn->setChecked(true);
    QRadioButton *bilinearBtn = new QRadioButton;
    bilinearBtn->setText("Bilinear Interpolation");

    btnGroup = new QButtonGroup;
    btnGroup->setExclusive(true);
    btnGroup->addButton(nearnestBtn, 0);
    btnGroup->addButton(bilinearBtn, 1);

    QHBoxLayout *opGroupLayout = new QHBoxLayout;
    opGroupLayout->addWidget(nearnestBtn);
    opGroupLayout->addWidget(bilinearBtn);
    opGroupLayout->setSpacing(10);
    opGroupLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *algoGroup = new QGroupBox(tr("Algorithm Setting"));
    algoGroup->setLayout(opGroupLayout);

    QLabel *scaleLabel = new QLabel;
    scaleLabel->setText("Scale Factor");
    scaleFactorEdit = new QLineEdit;
    scaleFactorEdit->setText("100");
    scaleFactorEdit->setMaximumWidth(50);
    QIntValidator *scaleValidator = new QIntValidator;
    scaleValidator->setRange(1, 999);
    scaleFactorEdit->setValidator(scaleValidator);
    QLabel *scaleSymbol = new QLabel;
    scaleSymbol->setText("%");
    scaleSymbol->setMaximumWidth(20);

    QHBoxLayout *scaleLayout = new QHBoxLayout;
    scaleLayout->addWidget(scaleLabel);
    scaleLayout->addWidget(scaleFactorEdit);
    scaleLayout->addWidget(scaleSymbol);
    scaleLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *rotateLabel = new QLabel;
    rotateLabel->setText("Rotation Degree");
    rotationDegreeEdit = new QLineEdit;
    rotationDegreeEdit->setText("0");
    rotationDegreeEdit->setMaximumWidth(50);
    QIntValidator *rotationValidator = new QIntValidator;
    rotationValidator->setRange(-180, 180);
    rotationDegreeEdit->setValidator(rotationValidator);
    QLabel *rotationSymbol = new QLabel;
    rotationSymbol->setText("°");
    rotationSymbol->setMaximumWidth(20);

    QHBoxLayout *rotationLayout = new QHBoxLayout;
    rotationLayout->addWidget(rotateLabel);
    rotationLayout->addWidget(rotationDegreeEdit);
    rotationLayout->addWidget(rotationSymbol);
    rotationLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *settingLayout = new QVBoxLayout;
    settingLayout->addLayout(scaleLayout);
    settingLayout->addLayout(rotationLayout);

    QGroupBox *settingGroup = new QGroupBox(tr("Parameter Setting"));
    settingGroup->setLayout(settingLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(algoGroup);
    mainLayout->addWidget(settingGroup);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &ScaleDialog::apply);

    setWindowTitle(tr("Scale/Rotation Dialog"));
    setMinimumWidth(500);
}

void ScaleDialog::apply(){
    QJsonObject obj;
    obj.insert("algo", btnGroup->checkedId());
    obj.insert("scale", scaleFactorEdit->text().toInt());
    obj.insert("rotation", rotationDegreeEdit->text().toInt());
    emit sendApplyScale(obj);
    close();
}
