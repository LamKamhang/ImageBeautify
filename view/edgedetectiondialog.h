#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include <QWidget>
#include <QDialog>
#include <QJsonObject>
QT_BEGIN_NAMESPACE
class QButtonGroup;
class QLineEdit;
class QStackedWidget;
QT_END_NAMESPACE

class SingleParaPage : public QWidget
{
    Q_OBJECT

public:
    SingleParaPage(QWidget *parent = 0);
    void getParam(int &);
    void setEditText(QString str);

private:
    QLineEdit *thresholdEdit;
};

class DualParaPage : public QWidget
{
    Q_OBJECT

public:
    DualParaPage(QWidget *parent = 0);
    void getParam(int &, int &);

private:
    QLineEdit *lowThresholdEdit;
    QLineEdit *highThresholdEdit;
};

class EdgeDetectionDialog : public QDialog
{
    Q_OBJECT

public:
    EdgeDetectionDialog();

signals:
    void sendApplyEdgeDetection(QJsonObject);

private slots:
    void apply();
    void pageChanged(int);

private:
    QButtonGroup *algoGroup;
    QStackedWidget *paramsPages;
    SingleParaPage *singlePage;
    DualParaPage *dualPage;

};

#endif // EDGEDETECTION_H
