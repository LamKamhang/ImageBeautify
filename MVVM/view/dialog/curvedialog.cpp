#include "curvedialog.h"
#include "QtWidgets"

CurveDialog::CurveDialog(std::shared_ptr<QImage> img)
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

    QRadioButton *linearBtn = new QRadioButton;
    linearBtn->setText(tr("Linear Curve"));
    linearBtn->setChecked(true);
    QRadioButton *piecewiseLinBtn = new QRadioButton;
    piecewiseLinBtn->setText(tr("Piecewise Linear Curve"));
    QRadioButton *expBtn = new QRadioButton;
    expBtn->setText(tr("Exponential Curve"));
    QRadioButton *logBtn = new QRadioButton;
    logBtn->setText(tr("Logarithm Curve"));

    btnGroup = new QButtonGroup;
    btnGroup->setExclusive(true);
    btnGroup->addButton(linearBtn, 0);
    btnGroup->addButton(piecewiseLinBtn, 1);
    btnGroup->addButton(expBtn, 2);
    btnGroup->addButton(logBtn, 3);

    QHBoxLayout *curveLayout1 = new QHBoxLayout;
    curveLayout1->addWidget(linearBtn);
    curveLayout1->addWidget(piecewiseLinBtn);

    QHBoxLayout *curveLayout2 = new QHBoxLayout;
    curveLayout2->addWidget(logBtn);
    curveLayout2->addWidget(expBtn);

    QVBoxLayout *curveLayout = new QVBoxLayout;
    curveLayout->addLayout(curveLayout1);
    curveLayout->addLayout(curveLayout2);
    curveLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *curveTypeBox = new QGroupBox(tr("Curve Type"));
    curveTypeBox->setLayout(curveLayout);

    canvas = new CurveCanvas(this, 256);

    QVBoxLayout *curveViewLayout = new QVBoxLayout;
    curveViewLayout->addWidget(canvas);
    curveViewLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *curveViewBox = new QGroupBox(tr("Curve View"));
    curveViewBox->setLayout(curveViewLayout);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *settingLayout = new QVBoxLayout;
    settingLayout->addWidget(curveTypeBox);
    settingLayout->addWidget(curveViewBox);
    settingLayout->addStretch(1);
    settingLayout->addSpacing(12);
    settingLayout->addLayout(btnLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(imageGroup);
    mainLayout->addLayout(settingLayout);
    setLayout(mainLayout);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &CurveDialog::apply);
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(curveTypeChanged(int)));
    connect(canvas, SIGNAL(linearCurveChanged(QPoint,QPoint)), this,
            SLOT(linearCurveChange(QPoint,QPoint)));
    connect(canvas, SIGNAL(pieceLinCurveChanged(QPoint,QPoint)), this,
            SLOT(pieceLinCurveChange(QPoint,QPoint)));
    connect(canvas, SIGNAL(logCurveChanged(double,double)), this,
            SLOT(logCurveChange(double,double)));
    connect(canvas, SIGNAL(expCurveChanged(double,double)), this,
            SLOT(expCurveChange(double,double)));

    setWindowTitle(tr("Contrast Curve Dialog"));
}

void CurveDialog::apply(){
    JsonParameters obj;
    QString t;
    CurveCanvas::CurveType type = (CurveCanvas::CurveType)btnGroup->checkedId();
    switch(type){
    case CurveCanvas::LINEAR:
        t = "Linear";
        break;
    case CurveCanvas::PIECEWISE_LINEAR:
        t = "Piecewice Linear";
        break;
    case CurveCanvas::LOGARITHM:
        t = "Logarithm";
        break;
    case CurveCanvas::EXPONENTIAL:
        t = "Exponential";
        break;
    default:
        break;
    }
    bool apply = true;
    obj.insert("apply",std::make_shared<BoolParameters>(apply));
    obj.insert("type",std::make_shared<QStringParameters>(t));
    obj.insert("a",std::make_shared<DoubleParameters>(m_a));
    obj.insert("b",std::make_shared<DoubleParameters>(m_b));
    obj.insert("p1",std::make_shared<QPointParameters>(m_p1));
    obj.insert("p2",std::make_shared<QPointParameters>(m_p2));
    emit sendApplyCurve(std::make_shared<JsonParameters>(obj));
    close();
}

void CurveDialog::logCurveChange(double a, double b){
    m_a = a; m_b = b;
    JsonParameters obj;
    bool apply = false;
    obj.insert("apply",std::make_shared<BoolParameters>(apply));
    QString t = "Logarithm";
    obj.insert("type",std::make_shared<QStringParameters>(t));
    obj.insert("a",std::make_shared<DoubleParameters>(m_a));
    obj.insert("b",std::make_shared<DoubleParameters>(m_b));
    obj.insert("p1",std::make_shared<QPointParameters>(m_p1));
    obj.insert("p2",std::make_shared<QPointParameters>(m_p2));
    emit sendApplyCurve(std::make_shared<JsonParameters>(obj));
}

void CurveDialog::expCurveChange(double a, double b){
    m_a = a; m_b = b;
    JsonParameters obj;
    bool apply = false;
    obj.insert("apply",std::make_shared<BoolParameters>(apply));
    QString t = "Exponential";
    obj.insert("type",std::make_shared<QStringParameters>(t));
    obj.insert("a",std::make_shared<DoubleParameters>(m_a));
    obj.insert("b",std::make_shared<DoubleParameters>(m_b));
    obj.insert("p1",std::make_shared<QPointParameters>(m_p1));
    obj.insert("p2",std::make_shared<QPointParameters>(m_p2));
    emit sendApplyCurve(std::make_shared<JsonParameters>(obj));
}

void CurveDialog::linearCurveChange(QPoint p1, QPoint p2){
    QPoint tmp1(p1);m_p1 = tmp1;
    QPoint tmp2(p2);m_p2 = tmp2;
    JsonParameters obj;
    bool apply = false;
    obj.insert("apply",std::make_shared<BoolParameters>(apply));
    QString t = "Linear";
    obj.insert("type",std::make_shared<QStringParameters>(t));
    obj.insert("a",std::make_shared<DoubleParameters>(m_a));
    obj.insert("b",std::make_shared<DoubleParameters>(m_b));
    obj.insert("p1",std::make_shared<QPointParameters>(m_p1));
    obj.insert("p2",std::make_shared<QPointParameters>(m_p2));
    emit sendApplyCurve(std::make_shared<JsonParameters>(obj));
}

void CurveDialog::pieceLinCurveChange(QPoint p1, QPoint p2){
    QPoint tmp1(p1);m_p1 = tmp1;
    QPoint tmp2(p2);m_p2 = tmp2;
    JsonParameters obj;
    bool apply = false;
    obj.insert("apply",std::make_shared<BoolParameters>(apply));
    QString t = "Piecewice Linear";
    obj.insert("type",std::make_shared<QStringParameters>(t));
    obj.insert("a",std::make_shared<DoubleParameters>(m_a));
    obj.insert("b",std::make_shared<DoubleParameters>(m_b));
    obj.insert("p1",std::make_shared<QPointParameters>(m_p1));
    obj.insert("p2",std::make_shared<QPointParameters>(m_p2));
    emit sendApplyCurve(std::make_shared<JsonParameters>(obj));
}

void CurveDialog::curveTypeChanged(int index){
    canvas->setType((CurveCanvas::CurveType)index);
}

void CurveDialog::setImage(std::shared_ptr<QImage> img){
    image = img;
}

void CurveDialog::update(){
    QPixmap pix = QPixmap::fromImage(*image);
    qreal h = pix.height();
    qreal w = pix.width();
    pix = pix.scaled(500, 500 * h / w, Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);
}
