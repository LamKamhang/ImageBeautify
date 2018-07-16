#include "algebraicdialog.h"
#include <QtWidgets>
#include <iostream>

AlgebraicDialog::AlgebraicDialog(QWidget *parent, QImage src)
    :QDialog(parent)
    ,img1(src)
    ,addContent(new AddContent)
    ,subtractContent(new SubtractContent)
    ,multiplyContent(new MultiplyContent)
{
    //初始化运算符选单
    QRadioButton *addOp = new QRadioButton(this);
    addOp->setText("Add(+)");
    QRadioButton *subtractOp = new QRadioButton(this);
    subtractOp->setText("Subtract(-)");
    QRadioButton *multiOp = new QRadioButton(this);
    multiOp->setText("Multiply(*)");

    btnGroup = new QButtonGroup(this);
    btnGroup->setExclusive(true);
    btnGroup->addButton(addOp, 0);
    btnGroup->addButton(subtractOp, 1);
    btnGroup->addButton(multiOp, 2);

    QHBoxLayout *opGroupLayout = new QHBoxLayout();
    opGroupLayout->addWidget(addOp);
    opGroupLayout->addWidget(subtractOp);
    opGroupLayout->addWidget(multiOp);
    opGroupLayout->setSpacing(10);
    opGroupLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *operationGroup = new QGroupBox(tr("Operator"));
    operationGroup->setLayout(opGroupLayout);

    //显示图像
    QLabel *srcImageLabel = new QLabel;
    srcImageLabel->setMaximumHeight(100);
    QPixmap pix = QPixmap::fromImage(img1);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(100 * w / h, 100, Qt::KeepAspectRatio);
    srcImageLabel->setPixmap(pix);

    QLabel *img1SizeLabel = new QLabel;
    img1SizeLabel->setText(tr("%1x%2").arg(w).arg(h));

    QVBoxLayout *img1Layout = new QVBoxLayout;
    img1Layout->addWidget(srcImageLabel);
    img1Layout->addWidget(img1SizeLabel);
    img1Layout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *img1Group = new QGroupBox(tr("Image 1"));
    img1Group->setLayout(img1Layout);

    operatedImgLabel = new QLabel;
    operatedImgLabel->setMaximumHeight(100);

    operatedImgSizeLabel = new QLabel;
    operatedImgSizeLabel->setText("");

    QVBoxLayout *img2Layout = new QVBoxLayout;
    img2Layout->addWidget(operatedImgLabel);
    img2Layout->addWidget(operatedImgSizeLabel);
    img2Layout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *img2Group = new QGroupBox(tr("Image 2"));
    img2Group->setLayout(img2Layout);

    QHBoxLayout *imgLayout = new QHBoxLayout;
    imgLayout->addWidget(img1Group);
    imgLayout->addWidget(img2Group);
    imgLayout->setContentsMargins(10, 10, 10, 10);

    QPushButton *openFileButton = new QPushButton(tr("Open..."));

    QHBoxLayout *openFileLayout = new QHBoxLayout;
    openFileLayout->addWidget(openFileButton);

    QVBoxLayout *imgViewLayout = new QVBoxLayout;
    imgViewLayout->addLayout(imgLayout);
    imgViewLayout->addLayout(openFileLayout);

    QGroupBox *imageGroup = new QGroupBox(tr("View Image"));
    imageGroup->setLayout(imgViewLayout);

    //选中运算符对应的操作
    operatorPages = new QStackedWidget();
    operatorPages->addWidget(addContent);
    operatorPages->addWidget(subtractContent);
    operatorPages->addWidget(multiplyContent);

    //默认选中Add
    addOp->setChecked(true);
    op = ADD;
    operatorPages->setCurrentIndex(0);

    //应用&退出
    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(imageGroup);
    mainLayout->addWidget(operationGroup);
    mainLayout->addWidget(operatorPages, 1);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    //绑定事件
    connect(btnGroup, SIGNAL(buttonClicked(QAbstractButton*)), this,
            SLOT(operatorButtonClicked(QAbstractButton*)));
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(openFileButton, &QAbstractButton::clicked, this, &AlgebraicDialog::openFile);
    connect(applyButton, &QAbstractButton::clicked, this, &AlgebraicDialog::apply);

    setWindowTitle(tr("Algebraic Operation Dialog"));
    setMinimumWidth(500);
}

void AlgebraicDialog::operatorButtonClicked(QAbstractButton*){
    int id = btnGroup->checkedId();
    op = (OperatorState)id;
//    std::cout<<op<<std::endl;
    if(id == 2){
        operatorPages->setCurrentIndex(2);
    }
    else{
        operatorPages->setCurrentIndex(0);
        if(id == 0){
            addContent->setGroupName("Add Setting");
        }
        else {
            addContent->setGroupName("Subtract Setting");
        }
    }

}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void AlgebraicDialog::openFile(){
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

bool AlgebraicDialog::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    img2 = newImage;
    QPixmap pix = QPixmap::fromImage(img2);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(100 * w / h, 100, Qt::KeepAspectRatio);
    operatedImgLabel->setPixmap(pix);

    operatedImgSizeLabel->setText(tr("%1x%2").arg(w).arg(h));

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(img2.width()).arg(img2.height()).arg(img2.depth());
    ((QMainWindow *)parentWidget())->statusBar()->showMessage(message);
    return true;
}

void AlgebraicDialog::apply(){
//    std::cout<<img2.isNull()<<std::endl;
    if(img2.isNull()){
        QMessageBox msgBox(QMessageBox::Warning, tr("Warning"), tr("Hasn't chosen the other image."));
        msgBox.exec();
        return;
    }
    QSize size1 = img1.size();
    QSize size2 = img2.size();
    if(size1!=size2){
        QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
                           tr("The size of two image is unequal. Image 1 is %1x%2, Image 2 is %3x%4.")
                           .arg(size1.width()).arg(size1.height()).arg(size2.width()).arg(size2.height()));
        msgBox.exec();
        return;
    }
    QJsonObject obj;
    bool dft;
    obj.insert("operator", op);
    switch(op){
    case ADD: case SUBTRACT:
        dft = addContent->isDefault();
        obj.insert("default", dft);
        if(!dft){
            double param1, param2;
            addContent->getParams(param1, param2);
            obj.insert("param1", param1);
            obj.insert("param2", param2);
        }
        break;
    default:
        break;
    }
    emit sendApplyAlgebraicOperation(obj, img2);
    close();
}

AddContent::AddContent(QWidget *parent)
    :QWidget(parent)
    ,defaultSetting(false)
{
    QCheckBox *defaultParaCheckBox = new QCheckBox(tr("Default Parameter(Simple Add/Subtract"));

    img1Para = new QLineEdit;
    img1Para->setText("0.5");

    QHBoxLayout *img1ParaLayout = new QHBoxLayout;
    img1ParaLayout->addWidget(img1Para);
    img1ParaLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *img1ParaGroupBox = new QGroupBox(tr("Parameter of Image 1"));
    img1ParaGroupBox->setLayout(img1ParaLayout);

    img2Para = new QLineEdit;
    img2Para->setText("0.5");

    QHBoxLayout *img2ParaLayout = new QHBoxLayout;
    img2ParaLayout->addWidget(img2Para);
    img2ParaLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *img2ParaGroupBox = new QGroupBox(tr("Parameter of Image 2"));
    img2ParaGroupBox->setLayout(img2ParaLayout);

    QHBoxLayout *imgParaLayout = new QHBoxLayout;
    imgParaLayout->addWidget(img1ParaGroupBox);
    imgParaLayout->addWidget(img2ParaGroupBox);
    imgParaLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *addLayout = new QVBoxLayout;
    addLayout->addWidget(defaultParaCheckBox);
    addLayout->addLayout(imgParaLayout);
    addLayout->setContentsMargins(10, 10, 10, 10);

    addGroupBox = new QGroupBox(tr("Add Settings"));
    addGroupBox->setLayout(addLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(addGroupBox);
    setLayout(mainLayout);

    QRegExp rx("^0(\\.[1-9])?$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    img1Para->setValidator(pReg);
    img2Para->setValidator(pReg);

    connect(defaultParaCheckBox, SIGNAL(clicked(bool)), this, SLOT(checkBoxClicked(bool)));
}

void AddContent::checkBoxClicked(bool checked) {
    img1Para->setEnabled(!checked);
    img2Para->setEnabled(!checked);
    defaultSetting = checked;
}

bool AddContent::isDefault(){
    return defaultSetting;
}

void AddContent::getParams(double &param1, double &param2){
    param1 = img1Para->text().toDouble();
    param2 = img2Para->text().toDouble();
}

void AddContent::setGroupName(QString str){
    addGroupBox->setTitle(str);
}

SubtractContent::SubtractContent(QWidget *parent)
    :QWidget(parent)
{

}

MultiplyContent::MultiplyContent(QWidget *parent)
    :QWidget(parent)
{
}
