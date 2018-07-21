#ifndef ALGEBRAICDIALOG_H
#define ALGEBRAICDIALOG_H
#include <QWidget>
#include <QDialog>
#include "../common/parameters.h"

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QButtonGroup;
class QImage;
class QLabel;
class QStackedWidget;
class QLineEdit;
class QGroupBox;
QT_END_NAMESPACE

class AddContent : public QWidget
{
    Q_OBJECT

public:
    AddContent(QWidget *parent = 0);
    bool isDefault();
    void getParams(double &, double &);
    void setGroupName(QString str);

private slots:
    void checkBoxClicked(bool);

private:
    QLineEdit *img1Para;
    QLineEdit *img2Para;
    QGroupBox *addGroupBox;
    bool defaultSetting;
};

class SubtractContent : public QWidget
{
public:
    SubtractContent(QWidget *parent = 0);
};

class MultiplyContent : public QWidget
{
public:
    MultiplyContent(QWidget *parent = 0);
};

class AlgebraicDialog : public QDialog
{
    Q_OBJECT

public:
    enum OperatorState{ADD = 0, SUBTRACT, MULTIPLY};

    AlgebraicDialog(QWidget *parent, QImage img1, std::shared_ptr<QImage> img2);
    void setImage2(std::shared_ptr<QImage> img);

signals:
    void sendApplyAlgebraicOperation(std::shared_ptr<JsonParameters>);
    void sendOpenFileImage2(QString);

private slots:
    void updateImage2();

    void operatorButtonClicked(QAbstractButton*);
    void openFile();
    void apply();

private:
    QButtonGroup *btnGroup;
    QStackedWidget *operatorPages;
    OperatorState op;

    QImage img1;
    std::shared_ptr<QImage> img2;
    QString filePath;
    QLabel *operatedImgLabel;
    QLabel *operatedImgSizeLabel;

    AddContent *addContent;
    SubtractContent *subtractContent;
    MultiplyContent *multiplyContent;
};

#endif // ALGEBRAICDIALOG_H
