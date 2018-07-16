#include "edgedetectiondialog.h"
#include <QtWidgets>

EdgeDetectionDialog::EdgeDetectionDialog()
    :singlePage(new SingleParaPage)
    ,dualPage(new DualParaPage)
{
    QRadioButton *sobelButton = new QRadioButton;
    sobelButton->setText(tr("Sobel"));
    QRadioButton *laplacianButton = new QRadioButton;
    laplacianButton->setText(tr("Laplacian"));
    QRadioButton *cannyButton = new QRadioButton;
    cannyButton->setText(tr("Canny"));

    algoGroup = new QButtonGroup;
    algoGroup->setExclusive(true);
    algoGroup->addButton(sobelButton, 0);
    algoGroup->addButton(laplacianButton, 1);
    algoGroup->addButton(cannyButton, 2);

    QHBoxLayout *algoLayout = new QHBoxLayout;
    algoLayout->addWidget(sobelButton);
    algoLayout->addWidget(laplacianButton);
    algoLayout->addWidget(cannyButton);
    algoLayout->addSpacing(12);
    algoLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *algoGroupBox = new QGroupBox(tr("Algorithm"));
    algoGroupBox->setLayout(algoLayout);

    paramsPages = new QStackedWidget;
    paramsPages->addWidget(singlePage);
    paramsPages->addWidget(dualPage);

    sobelButton->setChecked(true);
    paramsPages->setCurrentIndex(0);

    QHBoxLayout *thresholdLayout = new QHBoxLayout;
    thresholdLayout->addWidget(paramsPages);
    thresholdLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *thresholdGroup = new QGroupBox(tr("Threshold Setting"));
    thresholdGroup->setLayout(thresholdLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(algoGroupBox);
    mainLayout->addWidget(thresholdGroup);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &EdgeDetectionDialog::apply);
    connect(algoGroup, SIGNAL(buttonClicked(int)), this, SLOT(pageChanged(int)));

    setWindowTitle(tr("Edge Detection Dialog"));
}

void EdgeDetectionDialog::apply(){
    QJsonObject obj;
    int type = algoGroup->checkedId();
    obj.insert("type", type);
    if(type == 2){
        int lo, hi;
        dualPage->getParam(lo, hi);
        if(lo >= hi){
            QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
                               tr("Low threshold should be smaller than high threshold."));
            msgBox.exec();
            return;
        }
        obj.insert("lo", lo);
        obj.insert("hi",hi);
    } else {
        int th;
        singlePage->getParam(th);
        obj.insert("threshold", th);
    }
    emit sendApplyEdgeDetection(obj);
    close();
}

void EdgeDetectionDialog::pageChanged(int index){
    if(index == 2){
        paramsPages->setCurrentIndex(1);
    } else {
        if(index == 0){
            singlePage->setEditText(QString("90"));
        } else {
            singlePage->setEditText(QString("30"));
        }
        paramsPages->setCurrentIndex(0);
    }
}

SingleParaPage::SingleParaPage(QWidget *parent){
    QLabel *thresholdLabel = new QLabel;
    thresholdLabel->setText(tr("Threshold: "));

    thresholdEdit = new QLineEdit;
    thresholdEdit->setText("90");
    thresholdEdit->setMaximumWidth(50);

    QIntValidator *validator = new QIntValidator;
    validator->setRange(0, 255);
    thresholdEdit->setValidator(validator);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(thresholdLabel);
    mainLayout->addWidget(thresholdEdit);
    setLayout(mainLayout);
}

void SingleParaPage::getParam(int &param){
    param = thresholdEdit->text().toInt();
}

void SingleParaPage::setEditText(QString str){
    thresholdEdit->setText(str);
}

DualParaPage::DualParaPage(QWidget *parent){
    QLabel *lowLabel = new QLabel;
    lowLabel->setText(tr("Low Threshold"));

    lowThresholdEdit = new QLineEdit;
    lowThresholdEdit->setText("40");
    lowThresholdEdit->setMaximumWidth(50);

    QHBoxLayout *lowLayout = new QHBoxLayout;
    lowLayout->addWidget(lowLabel);
    lowLayout->addWidget(lowThresholdEdit);

    QLabel *highLabel = new QLabel;
    highLabel->setText(tr("High Threshold"));

    highThresholdEdit = new QLineEdit;
    highThresholdEdit->setText("80");
    highThresholdEdit->setMaximumWidth(50);

    QHBoxLayout *highLayout = new QHBoxLayout;
    highLayout->addWidget(highLabel);
    highLayout->addWidget(highThresholdEdit);

    QIntValidator *validator = new QIntValidator;
    validator->setRange(0, 255);
    lowThresholdEdit->setValidator(validator);
    highThresholdEdit->setValidator(validator);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(lowLayout);
    mainLayout->addLayout(highLayout);
    setLayout(mainLayout);
}

void DualParaPage::getParam(int &lo, int &hi){
    lo = lowThresholdEdit->text().toInt();
    hi = highThresholdEdit->text().toInt();
}
