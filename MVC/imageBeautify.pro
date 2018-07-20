#-------------------------------------------------
#
# Project created by QtCreator 2018-7-12T08:48:24
#
#-------------------------------------------------

QT       += core gui widgets
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imageBeautify
TEMPLATE = app


SOURCES += app/main.cpp \
    viewmodel/photoshopgui.cpp \
    model/log.cpp \
    model/imageoperations.cpp \
    view/algebraicdialog.cpp \
    view/huesaturalightdialog.cpp \
    view/dualthresholddialog.cpp \
    view/clipbox.cpp \
    view/scaledialog.cpp \
    view/filterdialog.cpp \
    view/edgedetectiondialog.cpp \
    view/houghtransformdialog.cpp \
    view/clipdialog.cpp \
    view/binarymorphodialog.cpp \
    view/graymorphodialog.cpp \
    view/structureelementcanvas.cpp \
    view/curvecanvas.cpp \
    view/curvedialog.cpp \
    view/histogramdialog.cpp \
    view/histogramview.cpp \
    view/leveldialog.cpp

HEADERS  += viewmodel/photoshopgui.h \
    model/log.h \
    model/imageoperations.h \
    view/algebraicdialog.h \
    view/huesaturalightdialog.h \
    view/dualthresholddialog.h \
    view/clipbox.h \
    view/scaledialog.h \
    view/filterdialog.h \
    view/edgedetectiondialog.h \
    view/houghtransformdialog.h \
    view/clipdialog.h \
    view/binarymorphodialog.h \
    view/graymorphodialog.h \
    view/structureelementcanvas.h \
    view/curvecanvas.h \
    view/curvedialog.h \
    view/histogramdialog.h \
    view/histogramview.h \
    view/leveldialog.h

FORMS    +=
