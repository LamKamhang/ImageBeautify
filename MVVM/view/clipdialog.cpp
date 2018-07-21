#include "clipdialog.h"
#include <QtWidgets>

ClipDialog::ClipDialog(QPixmap pixmap)
{
    this->setMouseTracking(true);

    w = pixmap.width();
    h = pixmap.height();
    maxWidth = 800;
    pixmap = pixmap.scaled(maxWidth, maxWidth * h / w, Qt::KeepAspectRatio);
    clipBox = new ClipBox(pixmap, this);
    clipBox->setMouseTracking(true);
    clipBox->show();

    QVBoxLayout *imageLayout = new QVBoxLayout;
    imageLayout->addWidget(clipBox);

    QGroupBox *imageGroup = new QGroupBox(tr("Image View"));
    imageGroup->setLayout(imageLayout);

    QLabel *leftLabel = new QLabel;
    leftLabel->setText("Left:");
    leftMarginLabel = new QLabel;
    leftMarginLabel->setAlignment(Qt::AlignRight);

    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(leftLabel);
    leftLayout->addWidget(leftMarginLabel);

    QLabel *rightLabel = new QLabel;
    rightLabel->setText("Right: ");
    rightMarginLabel = new QLabel;
    rightMarginLabel->setAlignment(Qt::AlignRight);

    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(rightLabel);
    rightLayout->addWidget(rightMarginLabel);

    QLabel *topLabel = new QLabel;
    topLabel->setText("Top: ");
    topMarginLabel = new QLabel;
    topMarginLabel->setAlignment(Qt::AlignRight);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(topLabel);
    topLayout->addWidget(topMarginLabel);

    QLabel *bottomLabel = new QLabel;
    bottomLabel->setText("Bottom: ");
    bottomMarginLabel = new QLabel;
    bottomMarginLabel->setAlignment(Qt::AlignRight);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(bottomLabel);
    bottomLayout->addWidget(bottomMarginLabel);

    QVBoxLayout *marginLayout = new QVBoxLayout;
    marginLayout->addLayout(leftLayout);
    marginLayout->addLayout(rightLayout);
    marginLayout->addLayout(topLayout);
    marginLayout->addLayout(bottomLayout);
    marginLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *clipmarginBox = new QGroupBox(tr("Clip Margins"));
    clipmarginBox->setLayout(marginLayout);

    applyButton = new QPushButton(tr("Apply"));
    applyButton->setEnabled(false);
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *rLayout = new QVBoxLayout;
    rLayout->addWidget(clipmarginBox);
    rLayout->addStretch(1);
    rLayout->addSpacing(12);
    rLayout->addLayout(btnLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(imageGroup);
    mainLayout->addLayout(rLayout);
    setLayout(mainLayout);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &ClipDialog::apply);
    connect(clipBox, SIGNAL(sendEnable()), this, SLOT(receiveEnable()));
    connect(clipBox, SIGNAL(currentRect(QRect)), this, SLOT(setEdit(QRect)));

    setWindowTitle(tr("Clip Dialog"));
}

void ClipDialog::apply(){
    JsonParameters obj;
    int left = leftMarginLabel->text().toInt();
    int right = w - rightMarginLabel->text().toInt();
    int top = topMarginLabel->text().toInt();
    int bottom = h - bottomMarginLabel->text().toInt();
    obj.insert("left", std::make_shared<IntParameters>(left));
    obj.insert("right", std::make_shared<IntParameters>(right));
    obj.insert("top", std::make_shared<IntParameters>(top));
    obj.insert("bottom", std::make_shared<IntParameters>(bottom));
    emit sendApplyClip(std::make_shared<JsonParameters>(obj));
    close();
}

void ClipDialog::receiveEnable(){
    applyButton->setEnabled(true);
}

void ClipDialog::setEdit(QRect rect){
    int left = rect.left() * w / maxWidth;
    int right = w - rect.right() * w / maxWidth;
    int top = rect.top() * w / maxWidth;
    int bottom = h - rect.bottom() * w / maxWidth;
    leftMarginLabel->setText(QString::number(left));
    rightMarginLabel->setText(QString::number(right));
    topMarginLabel->setText(QString::number(top));
    bottomMarginLabel->setText(QString::number(bottom));
}
