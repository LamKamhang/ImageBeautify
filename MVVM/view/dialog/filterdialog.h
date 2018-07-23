#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QWidget>
#include <QDialog>
#include "../../common/parameters.h"
QT_BEGIN_NAMESPACE
class QButtonGroup;
class QLineEdit;
QT_END_NAMESPACE

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    FilterDialog();

signals:
    void sendApplyFilter(std::shared_ptr<JsonParameters> json);

private slots:
    void apply();
    void buttonGroupChanged(int);

private:
    QButtonGroup *btnGroup;
    QLineEdit *colEdit;
    QLineEdit *rowEdit;
    QLineEdit *anchorXEdit;
    QLineEdit *anchorYEdit;
    QLineEdit *sigmaXEdit;
};

#endif // FILTERDIALOG_H
