#include "binarymorphodialog.h"
#include <QtWidgets>

BinaryMorphoDialog::BinaryMorphoDialog()
{
    QRadioButton *dilationBtn = new QRadioButton;
    dilationBtn->setText(tr("Dilation"));
    dilationBtn->setChecked(true);
    QRadioButton *erosionBtn = new QRadioButton;
    erosionBtn->setText(tr("Erosion"));
    QRadioButton *openingBtn = new QRadioButton;
    openingBtn->setText(tr("Opening"));
    QRadioButton *closingBtn = new QRadioButton;
    closingBtn->setText(tr("Closing"));
    QRadioButton *thinningBtn = new QRadioButton;
    thinningBtn->setText(tr("Thinning"));
    QRadioButton *thickingBtn = new QRadioButton;
    thickingBtn->setText(tr("Thicking"));
    QRadioButton *distanceTransBtn = new QRadioButton;
    distanceTransBtn->setText(tr("Distance Transform"));
    QRadioButton *skeletonizationBtn = new QRadioButton;
    skeletonizationBtn->setText(tr("Skeletonization"));
    QRadioButton *skeleReconstructBtn = new QRadioButton;
    skeleReconstructBtn->setText(tr("Skeleton Reconstruction"));
    QRadioButton *reconstructionBtn = new QRadioButton;
    reconstructionBtn->setText(tr("Reconstruction"));

    btnGroup = new QButtonGroup;
    btnGroup->setExclusive(true);
    btnGroup->addButton(dilationBtn, 0);
    btnGroup->addButton(erosionBtn, 1);
    btnGroup->addButton(openingBtn, 2);
    btnGroup->addButton(closingBtn, 3);
    btnGroup->addButton(thinningBtn, 4);
    btnGroup->addButton(thickingBtn, 5);
    btnGroup->addButton(distanceTransBtn, 6);
    btnGroup->addButton(skeletonizationBtn, 7);
    btnGroup->addButton(skeleReconstructBtn, 8);
    btnGroup->addButton(reconstructionBtn, 9);

    QHBoxLayout *btnLayout1 = new QHBoxLayout;
    btnLayout1->addWidget(dilationBtn);
    btnLayout1->addWidget(erosionBtn);
    btnLayout1->addWidget(openingBtn);

    QHBoxLayout *btnLayout2 = new QHBoxLayout;
    btnLayout2->addWidget(closingBtn);
    btnLayout2->addWidget(thinningBtn);
    btnLayout2->addWidget(thickingBtn);

    QHBoxLayout *btnLayout3 = new QHBoxLayout;
    btnLayout3->addWidget(distanceTransBtn);
    btnLayout3->addWidget(skeletonizationBtn);

    QHBoxLayout *btnLayout4 = new QHBoxLayout;
    btnLayout4->addWidget(skeleReconstructBtn);
    btnLayout4->addWidget(reconstructionBtn);

    QVBoxLayout *btnLayout = new QVBoxLayout;
    btnLayout->addLayout(btnLayout1);
    btnLayout->addLayout(btnLayout2);
    btnLayout->addLayout(btnLayout3);
    btnLayout->addLayout(btnLayout4);
    btnLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *opGroup = new QGroupBox(tr("Morphology Operation"));
    opGroup->setLayout(btnLayout);

    QLabel *sizeLabel = new QLabel;
    sizeLabel->setText(tr("Size"));
    elementSizeBox = new QComboBox;
    elementSizeBox->addItem(tr("3x3"));
    elementSizeBox->addItem(tr("5x5"));
    elementSizeBox->addItem(tr("7x7"));

    QHBoxLayout *sizeLayout = new QHBoxLayout;
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(elementSizeBox);

    canvas = new StructureElementCanvas(this, 3, 400);
    size = 3;

    QVBoxLayout *structureElemLayout = new QVBoxLayout;
    structureElemLayout->addLayout(sizeLayout);
    structureElemLayout->addWidget(canvas);
    structureElemLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *structureElemGroup = new QGroupBox(tr("Structure Element"));
    structureElemGroup->setLayout(structureElemLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(opGroup);
    mainLayout->addWidget(structureElemGroup);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &BinaryMorphoDialog::apply);
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupChanged(int)));
    connect(elementSizeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(structureElementSizeChanged(int)));

    setWindowTitle(tr("Binary Morphology Dialog"));
}

void BinaryMorphoDialog::apply(){
    QJsonObject obj;
    int opIndex = btnGroup->checkedId();
    obj.insert("operation", opIndex);
    obj.insert("size", size);
    QJsonArray array;
    canvas->getElementArray(array);
    obj.insert("elem", array);
    int x,y;
    canvas->getAnchor(x, y);
    obj.insert("x", x);
    obj.insert("y", y);
    emit sendApplyBinaryMorpho(obj);
    close();
}

void BinaryMorphoDialog::buttonGroupChanged(int index){
    OperationType type = (OperationType)index;
    if(type == THINING || type == THICKING  || type == DISTANCE_TRANSFORM){
        canvas->setEnabled(false);
        elementSizeBox->setEnabled(false);
    } else {
        canvas->setEnabled(true);
        elementSizeBox->setEnabled(true);
    }
}

void BinaryMorphoDialog::structureElementSizeChanged(int index){
    switch(index){
    case 0:
        size = 3;
        break;
    case 1:
        size = 5;
        break;
    case 2:
        size = 7;
        break;
    default:
        break;
    }
    canvas->sizeChange(size);
}
