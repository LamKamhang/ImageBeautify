#ifndef BINARYMORPHODIALOG_H
#define BINARYMORPHODIALOG_H

#include <QWidget>
#include <QDialog>
#include <QJsonObject>
#include "structureelementcanvas.h"
QT_BEGIN_NAMESPACE
class QButtonGroup;
class QComboBox;
QT_END_NAMESPACE

class BinaryMorphoDialog : public QDialog
{
    Q_OBJECT

public:
    enum OperationType{DILATION = 0, EROSION, OPENING, CLOSING,
                      THINING, THICKING, DISTANCE_TRANSFORM,
                      SKELETONIZATION, SKELETON_RECONSTRUCTION,
                      RECONSTRUCTION};

    BinaryMorphoDialog();

signals:
    void sendApplyBinaryMorpho(QJsonObject);

private slots:
    void apply();
    void buttonGroupChanged(int);
    void structureElementSizeChanged(int);

private:
    QComboBox *elementSizeBox;
    QButtonGroup *btnGroup;
    StructureElementCanvas *canvas;
    int size;
};

#endif // BINARYMORPHODIALOG_H
