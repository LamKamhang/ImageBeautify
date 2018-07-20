#ifndef HOUGHTRANSFORMDIALOG_H
#define HOUGHTRANSFORMDIALOG_H

#include <QWidget>
#include <QJsonObject>
#include <QDialog>
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class HoughTransformDialog : public QDialog
{
    Q_OBJECT

public:
    HoughTransformDialog();

signals:
    void sendApplyHoughTransform(QJsonObject);

private slots:
    void apply();

private:
    QLineEdit *loRadiusEdit;
    QLineEdit *hiRadiusEdit;
};

#endif // HOUGHTRANSFORMDIALOG_H
