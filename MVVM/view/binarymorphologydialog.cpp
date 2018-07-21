#include "binarymorphologydialog.h"
#include <QtWidgets>

BinaryMorphologyDialog::BinaryMorphologyDialog()
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
    btnGroup->addButton(dilationBtn, DILATION);
    btnGroup->addButton(erosionBtn, EROSION);
    btnGroup->addButton(openingBtn, OPENING);
    btnGroup->addButton(closingBtn, CLOSING);
    btnGroup->addButton(thinningBtn, THINNING);
    btnGroup->addButton(thickingBtn, THICKING);
    btnGroup->addButton(distanceTransBtn, DISTANCE_TRANSFORM);
    btnGroup->addButton(skeletonizationBtn, SKELETONIZATION);
    btnGroup->addButton(skeleReconstructBtn, SKELETON_RECONSTRUCTION);
    btnGroup->addButton(reconstructionBtn, RECONSTRUCTION);

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
    connect(applyButton, &QAbstractButton::clicked, this, &BinaryMorphologyDialog::apply);
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupChanged(int)));
    connect(elementSizeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(structureElementSizeChanged(int)));

    setWindowTitle(tr("Binary Morphology Dialog"));
}

void BinaryMorphologyDialog::apply(){
    JsonParameters json;
    int opIndex = btnGroup->checkedId();
    json.insert("operation", std::make_shared<IntParameters>(opIndex));
    json.insert("size", std::make_shared<IntParameters>(size));
    std::vector<int> array;
    canvas->getElementArray(array);
    VectorParameters<int> elem(array);
    json.insert("elem", std::make_shared<VectorParameters<int> >(elem));
    int x, y;
    canvas->getAnchor(x, y);
    json.insert("x", std::make_shared<IntParameters>(x));
    json.insert("y", std::make_shared<IntParameters>(y));
    emit sendApplyBinaryMorphology(std::make_shared<JsonParameters>(json));
    close();
}

void BinaryMorphologyDialog::buttonGroupChanged(int index){
    OperationType type = (OperationType)index;
    if(type == THINNING || type == THICKING  || type == DISTANCE_TRANSFORM){
        canvas->setEnabled(false);
        elementSizeBox->setEnabled(false);
    } else {
        canvas->setEnabled(true);
        elementSizeBox->setEnabled(true);
    }
}

void BinaryMorphologyDialog::structureElementSizeChanged(int index){
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
