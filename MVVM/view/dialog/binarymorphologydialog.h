#pragma once

#include <QWidget>
#include <QDialog>
#include <QJsonObject>
#include "structureelementcanvas.h"
#include "../../common/parameters.h"
#include "../../common/type.h"
QT_BEGIN_NAMESPACE
class QButtonGroup;
class QComboBox;
QT_END_NAMESPACE

class BinaryMorphologyDialog : public QDialog
{
    Q_OBJECT

public:
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
