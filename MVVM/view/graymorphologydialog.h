#pragma once

#include <QWidget>
#include <QDialog>
#include "structureelementcanvas.h"
#include "../common/parameters.h"
#include "../common/type.h"

QT_BEGIN_NAMESPACE
class QButtonGroup;
class QComboBox;
QT_END_NAMESPACE

class GrayMorphologyDialog : public QDialog
{
    Q_OBJECT

public:
    GrayMorphologyDialog();

signals:
    void sendApplyGrayMorphology(std::shared_ptr<JsonParameters>);

private slots:
    void apply();
    void structureElementSizeChanged(int);

private:
    QComboBox *elementSizeBox;
    QButtonGroup *btnGroup;
    StructureElementCanvas *canvas;
    int size;
};
