#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H
#include <QWidget>
#include <QDialog>
#include "../../common/parameters.h"
QT_BEGIN_NAMESPACE
class QLineEdit;
class QButtonGroup;
QT_END_NAMESPACE

class ScaleDialog : public QDialog
{
    Q_OBJECT

public:
    ScaleDialog();

signals:
    void sendApplyScale(std::shared_ptr<JsonParameters>);

private slots:
    void apply();

private:
    QButtonGroup *btnGroup;
    QLineEdit *scaleFactorEdit;
    QLineEdit *rotationDegreeEdit;
};

#endif // SCALEDIALOG_H
