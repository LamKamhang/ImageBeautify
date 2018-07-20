#include "histogramdialog.h"
#include <QtWidgets>

HistogramDialog::HistogramDialog(QImage img)
    : image(img)
{
    histogram = new int[256];
    imageOp->getHistogram(img, histogram);
    view = new HistogramView(histogram, 512, 200);

    QPushButton *applyButton = new QPushButton(tr("Histogram Equalization"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(view);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(applyButton, &QAbstractButton::clicked, this, &HistogramDialog::histogramEqualize);

    setWindowTitle(tr("Histogram Dialog"));
}

void HistogramDialog::histogramEqualize(){
    image = imageOp->histogramEqualization(image, histogram);
    emit sendApplyHistogramEqualization(image);
    close();
}
