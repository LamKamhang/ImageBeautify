#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H
#include <QWidget>
#include <QDialog>
#include <vector>
#include "histogramview.h"
#include "../../common/parameters.h"

class HistogramDialog : public QDialog
{
    Q_OBJECT
public:
    HistogramDialog(std::shared_ptr<QImage> img);

signals:
    void sendApplyHistogramEqualization(std::shared_ptr<VectorParameters<int> > param);

private slots:
    void histogramEqualize();

private:
    void getHistogram(QImage img, int *histo);

private:
    std::shared_ptr<QImage> image;
    std::vector<int> histo;
    HistogramView *view;
};

#endif // HISTOGRAMDIALOG_H
