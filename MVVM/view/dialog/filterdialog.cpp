#include "filterdialog.h"
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

FilterDialog::FilterDialog()
{
    QRadioButton *meanFilter = new QRadioButton;
    meanFilter->setText(tr("Mean Filter"));
    meanFilter->setChecked(true);
    QRadioButton *medianFilter = new QRadioButton;
    medianFilter->setText(tr("Median Filter"));
    QRadioButton *gaussianFilter = new QRadioButton;
    gaussianFilter->setText(tr("Gaussian Filter"));

    btnGroup = new QButtonGroup;
    btnGroup->setExclusive(true);
    btnGroup->addButton(meanFilter, 0);
    btnGroup->addButton(medianFilter, 1);
    btnGroup->addButton(gaussianFilter, 2);

    QHBoxLayout *filterTypeGroupLayout = new QHBoxLayout;
    filterTypeGroupLayout->addWidget(meanFilter);
    filterTypeGroupLayout->addWidget(medianFilter);
    filterTypeGroupLayout->addWidget(gaussianFilter);
    filterTypeGroupLayout->setSpacing(10);
    filterTypeGroupLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *filterTypeGroup = new QGroupBox(tr("Filter Type"));
    filterTypeGroup->setLayout(filterTypeGroupLayout);

    QLabel *sizeLabel = new QLabel;
    sizeLabel->setText(tr("Size: "));
    QLabel *leftParenthesisLabel = new QLabel;
    leftParenthesisLabel->setAlignment(Qt::AlignRight);
    leftParenthesisLabel->setMaximumWidth(10);
    leftParenthesisLabel->setText("(");
    colEdit = new QLineEdit;
    colEdit->setText("3");
    colEdit->setMaximumWidth(50);
    QLabel *commaLabel = new QLabel;
    commaLabel->setMaximumWidth(10);
    commaLabel->setText(",");
    rowEdit = new QLineEdit;
    rowEdit->setText("3");
    rowEdit->setMaximumWidth(50);
    QLabel *rightParenthesisLabel = new QLabel;
    rightParenthesisLabel->setMaximumWidth(10);
    rightParenthesisLabel->setText(")");
    QIntValidator *sizeValidator = new QIntValidator;
    sizeValidator->setRange(2, 50);
    colEdit->setValidator(sizeValidator);
    rowEdit->setValidator(sizeValidator);

    QHBoxLayout *sizeLayout = new QHBoxLayout;
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(leftParenthesisLabel);
    sizeLayout->addWidget(colEdit);
    sizeLayout->addWidget(commaLabel);
    sizeLayout->addWidget(rowEdit);
    sizeLayout->addWidget(rightParenthesisLabel);
    sizeLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *anchorLabel = new QLabel;
    anchorLabel->setText(tr("Anchor: "));
    QLabel *lpLabel = new QLabel;
    lpLabel->setAlignment(Qt::AlignRight);
    lpLabel->setMaximumWidth(10);
    lpLabel->setText("(");
    anchorXEdit = new QLineEdit;
    anchorXEdit->setText("-1");
    anchorXEdit->setMaximumWidth(50);
    QLabel *cmLabel = new QLabel;
    cmLabel->setMaximumWidth(10);
    cmLabel->setText(",");
    anchorYEdit = new QLineEdit;
    anchorYEdit->setText("-1");
    anchorYEdit->setMaximumWidth(50);
    QLabel *rpLabel = new QLabel;
    rpLabel->setMaximumWidth(10);
    rpLabel->setText(")");
    QIntValidator *anchorValidator = new QIntValidator;
    anchorValidator->setRange(-1, 50);
    anchorXEdit->setValidator(anchorValidator);
    anchorYEdit->setValidator(anchorValidator);

    QHBoxLayout *anchorLayout = new QHBoxLayout;
    anchorLayout->addWidget(anchorLabel);
    anchorLayout->addWidget(lpLabel);
    anchorLayout->addWidget(anchorXEdit);
    anchorLayout->addWidget(cmLabel);
    anchorLayout->addWidget(anchorYEdit);
    anchorLayout->addWidget(rpLabel);
    anchorLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *sigmaXLabel = new QLabel;
    sigmaXLabel->setText(tr("Sigma: "));
    sigmaXEdit = new QLineEdit;
    sigmaXEdit->setText("0.5");
    sigmaXEdit->setMaximumWidth(50);

    QHBoxLayout *sigmaXLayout = new QHBoxLayout;
    sigmaXLayout->addWidget(sigmaXLabel);
    sigmaXLayout->addWidget(sigmaXEdit);
    sigmaXLayout->setContentsMargins(10, 10, 10, 10);

    QDoubleValidator *sigmaValidator = new QDoubleValidator;
    sigmaValidator->setRange(0, 10, 1);
    sigmaXEdit->setValidator(sigmaValidator);
    sigmaXEdit->setEnabled(false);

    QVBoxLayout *settingLayout = new QVBoxLayout;
    settingLayout->addLayout(sizeLayout);
    settingLayout->addLayout(anchorLayout);
    settingLayout->addLayout(sigmaXLayout);

    QGroupBox *settingGroup = new QGroupBox(tr("Filter Kernel Setting"));
    settingGroup->setLayout(settingLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(filterTypeGroup);
    mainLayout->addWidget(settingGroup);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &FilterDialog::apply);
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupChanged(int)));

    setWindowTitle(tr("Filter Dialog"));
}

void FilterDialog::apply(){
    JsonParameters json;
    int type = btnGroup->checkedId();
    json.insert("type", std::make_shared<IntParameters>(type));
    int col = colEdit->text().toInt();
    json.insert("col",std::make_shared<IntParameters>(col));
    int row = rowEdit->text().toInt();
    json.insert("row",std::make_shared<IntParameters>(row));
    int anchorX = anchorXEdit->text().toInt();
    int anchorY = anchorYEdit->text().toInt();
    if(anchorX >= col || anchorY >= row){
        QMessageBox msgBox(QMessageBox::Warning, tr("Warning"), tr("Illegal anchor."));
        msgBox.exec();
        return;
    }
    json.insert("x",std::make_shared<IntParameters>(anchorX));
    json.insert("y",std::make_shared<IntParameters>(anchorY));
    if(type == 2){
        double sigma = sigmaXEdit->text().toDouble();
        json.insert("sigma",std::make_shared<DoubleParameters>(sigma));
    }
    emit sendApplyFilter(std::make_shared<JsonParameters>(json));
    close();
}

void FilterDialog::buttonGroupChanged(int id){
    if(id == 2){
        sigmaXEdit->setEnabled(true);
    } else {
        sigmaXEdit->setEnabled(false);
    }
}
