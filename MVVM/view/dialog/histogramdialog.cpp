#include "histogramdialog.h"
#include <QtWidgets>

HistogramDialog::HistogramDialog(std::shared_ptr<QImage> img)
    : image(img)
    , histo(256)
{
    getHistogram(*img, &histo[0]);
    
    view = new HistogramView(&histo[0], 512, 200);

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
    VectorParameters<int> param(histo);
    emit sendApplyHistogramEqualization(std::make_shared<VectorParameters<int> >(param));
    close();
}


void HistogramDialog::getHistogram(QImage img, int *histo){
    for(int i = 0; i < 256; i++){
        histo[i] = 0;
    }
    int w = img.width();
    int h = img.height();
    int v;
    QRgb *line;
    QColor color;
    for(int j = 0; j < h; j++){
        line = (QRgb *)img.scanLine(j);
        for(int i = 0; i < w; i++){
            color = QColor(line[i]);
            v = color.lightness();
            histo[v]++;
        }
    }
}
