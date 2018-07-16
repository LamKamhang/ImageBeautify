#include "graymorphodialog.h"
#include <QtWidgets>

GrayMorphoDialog::GrayMorphoDialog()
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
    QRadioButton *obrBtn = new QRadioButton;
    obrBtn->setText(tr("Opening By Reconstruction"));
    QRadioButton *cbrBtn = new QRadioButton;
    cbrBtn->setText(tr("Closing By Reconstruction"));
    QRadioButton *watershedBtn = new QRadioButton;
    watershedBtn->setText(tr("Watershed"));

    btnGroup = new QButtonGroup;
    btnGroup->setExclusive(true);
    btnGroup->addButton(dilationBtn, 0);
    btnGroup->addButton(erosionBtn, 1);
    btnGroup->addButton(openingBtn, 2);
    btnGroup->addButton(closingBtn, 3);
    btnGroup->addButton(obrBtn, 4);
    btnGroup->addButton(cbrBtn, 5);
    btnGroup->addButton(watershedBtn, 6);

    QHBoxLayout *btnLayout1 = new QHBoxLayout;
    btnLayout1->addWidget(dilationBtn);
    btnLayout1->addWidget(erosionBtn);
    btnLayout1->addWidget(openingBtn);

    QHBoxLayout *btnLayout2 = new QHBoxLayout;
    btnLayout2->addWidget(closingBtn);
    btnLayout2->addWidget(watershedBtn);

    QVBoxLayout *opLayout = new QVBoxLayout;
    opLayout->addLayout(btnLayout1);
    opLayout->addLayout(btnLayout2);
    opLayout->addWidget(obrBtn);
    opLayout->addWidget(cbrBtn);
    opLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *opGroup = new QGroupBox(tr("Morphology Operation"));
    opGroup->setLayout(opLayout);

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
    connect(applyButton, &QAbstractButton::clicked, this, &GrayMorphoDialog::apply);
    connect(elementSizeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(structureElementSizeChanged(int)));

    setWindowTitle(tr("Grayscale Morphology Dialog"));
}

void GrayMorphoDialog::apply(){
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
    emit sendApplyGrayMorpho(obj);
    close();
}

void GrayMorphoDialog::structureElementSizeChanged(int index){
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
