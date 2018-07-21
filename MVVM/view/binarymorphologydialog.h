#pragma once

#include <QWidget>
#include <QDialog>
#include <QJsonObject>
#include "structureelementcanvas.h"
#include "../common/parameters.h"
QT_BEGIN_NAMESPACE
class QButtonGroup;
class QComboBox;
QT_END_NAMESPACE

class BinaryMorphologyDialog : public QDialog
{
    Q_OBJECT

public:
    enum OperationType{DILATION = 0, EROSION, OPENING, CLOSING,
                      THINING, THICKING, DISTANCE_TRANSFORM,
                      SKELETONIZATION, SKELETON_RECONSTRUCTION,
                      RECONSTRUCTION};

    BinaryMorphologyDialog();

signals:
    void sendApplyBinaryMorphology(std::shared_ptr<JsonParameters>);

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
