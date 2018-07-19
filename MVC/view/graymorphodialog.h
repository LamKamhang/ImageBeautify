#ifndef GRAYMORPHODIALOG_H
#define GRAYMORPHODIALOG_H

#include <QWidget>
#include <QDialog>
#include <QJsonObject>
#include "structureelementcanvas.h"
QT_BEGIN_NAMESPACE
class QButtonGroup;
class QComboBox;
QT_END_NAMESPACE

class GrayMorphoDialog : public QDialog
{
    Q_OBJECT

public:
    enum OperationType{DILATION = 0, EROSION, OPENING, CLOSING,
                      OBR, CBR, WATERSHED};

    GrayMorphoDialog();

signals:
    void sendApplyGrayMorpho(QJsonObject);

private slots:
    void apply();
    void structureElementSizeChanged(int);

private:
    QComboBox *elementSizeBox;
    QButtonGroup *btnGroup;
    StructureElementCanvas *canvas;
    int size;
};

#endif // GRAYMORPHODIALOG_H
