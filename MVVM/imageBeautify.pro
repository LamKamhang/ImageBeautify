#-------------------------------------------------
#
# Project created by QtCreator 2018-07-13T14:04:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imageBeautify
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx {
LIBS += /usr/local/Cellar/opencv/3.4.1_2/lib/libopencv_highgui.dylib \
        /usr/local/Cellar/opencv/3.4.1_2/lib/libopencv_core.dylib \
        /usr/local/Cellar/opencv/3.4.1_2/lib/libopencv_imgproc.dylib \
        /usr/local/Cellar/opencv/3.4.1_2/lib/libopencv_imgcodecs.dylib \
        /usr/local/Cellar/opencv/3.4.1_2/lib/libopencv_*.dylib

INCLUDEPATH += /usr/local/Cellar/opencv/3.4.1_2/include/
}

unix:!macx {
LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so\
        /usr/local/lib/libopencv_*.so
}

win32 {
CONFIG(debug, debug|release): LIBS += -L$$PWD/../OpenCV/win32/lib/ -lopencv_world342d
CONFIG(release, debug|release): LIBS += -L$$PWD/../OpenCV/win32/lib/ -lopencv_world342

INCLUDEPATH += $$PWD/../OpenCV/win32/include
DEPENDPATH += $$PWD/../OpenCV/win32/include
}

CONFIG += c++14



RESOURCES += \
    effectsicons.qrc

HEADERS += \
    app/app.h \
    common/etlbase.h \
    common/parameters.h \
    common/type.h \
    common/util.h \
    model/filters/art_effect.h \
    model/filters/classic_effect.h \
    model/imageoperation/aux_image_alg.h \
    model/logoperation/aux_log_alg.h \
    model/model.h \
    view/dialog/algebraicdialog.h \
    view/dialog/binarymorphologydialog.h \
    view/dialog/classicspecialeffectdialog.h \
    view/dialog/clickableqlabel.h \
    view/dialog/clipbox.h \
    view/dialog/clipdialog.h \
    view/dialog/curvecanvas.h \
    view/dialog/curvedialog.h \
    view/dialog/dualthresholddialog.h \
    view/dialog/edgedetectiondialog.h \
    view/dialog/filterdialog.h \
    view/dialog/graymorphologydialog.h \
    view/dialog/histogramdialog.h \
    view/dialog/histogramview.h \
    view/dialog/houghcircledetectiondialog.h \
    view/dialog/huesaturalightdialog.h \
    view/dialog/leveldialog.h \
    view/dialog/scaledialog.h \
    view/dialog/specialeffectdialog.h \
    view/dialog/structureelementcanvas.h \
    view/sinks/maincommandsink.h \
    view/sinks/mainimagesink.h \
    view/mainview.h \
    viewmodel/commands/AlgebraicCommand.h \
    viewmodel/commands/arteffectscommand.h \
    viewmodel/commands/BinaryMorphologyCommand.h \
    viewmodel/commands/channelcommand.h \
    viewmodel/commands/classiceffectscommand.h \
    viewmodel/commands/ClipCommand.h \
    viewmodel/commands/CurveCommand.h \
    viewmodel/commands/dualthresholdcommand.h \
    viewmodel/commands/edgedetectioncommand.h \
    viewmodel/commands/filtercommand.h \
    viewmodel/commands/GrayMorphologyCommand.h \
    viewmodel/commands/grayscaletransfercommand.h \
    viewmodel/commands/HistogramCommand.h \
    viewmodel/commands/houghcircledetectioncommand.h \
    viewmodel/commands/houghlinedetectioncommand.h \
    viewmodel/commands/huesaturalightcommand.h \
    viewmodel/commands/LevelCommand.h \
    viewmodel/commands/openfilecommand.h \
    viewmodel/commands/opensubdialogcommand.h \
    viewmodel/commands/opensubfilecommand.h \
    viewmodel/commands/otsucommand.h \
    viewmodel/commands/redocommand.h \
    viewmodel/commands/savefilecommand.h \
    viewmodel/commands/ScaleCommand.h \
    viewmodel/commands/undocommand.h \
    viewmodel/sinks/viewmodelsink.h \
    viewmodel/viewmodel.h

SOURCES += \
    app/app.cpp \
    app/main.cpp \
    common/util.cpp \
    model/filteroperation/filteroperation.cpp \
    model/filters/art_effect.cpp \
    model/filters/classic_effect.cpp \
    model/imageoperation/aux_image_alg.cpp \
    model/imageoperation/imageoperation.cpp \
    model/logoperation/aux_log_alg.cpp \
    model/logoperation/logoperation.cpp \
    model/model.cpp \
    view/dialog/algebraicdialog.cpp \
    view/dialog/binarymorphologydialog.cpp \
    view/dialog/classicspecialeffectdialog.cpp \
    view/dialog/clickableqlabel.cpp \
    view/dialog/clipbox.cpp \
    view/dialog/clipdialog.cpp \
    view/dialog/curvecanvas.cpp \
    view/dialog/curvedialog.cpp \
    view/dialog/dualthresholddialog.cpp \
    view/dialog/edgedetectiondialog.cpp \
    view/dialog/filterdialog.cpp \
    view/dialog/graymorphologydialog.cpp \
    view/dialog/histogramdialog.cpp \
    view/dialog/histogramview.cpp \
    view/dialog/houghcircledetectiondialog.cpp \
    view/dialog/huesaturalightdialog.cpp \
    view/dialog/leveldialog.cpp \
    view/dialog/scaledialog.cpp \
    view/dialog/specialeffectdialog.cpp \
    view/dialog/structureelementcanvas.cpp \
    view/sinks/maincommandsink.cpp \
    view/sinks/mainimagesink.cpp \
    view/mainview.cpp \
    viewmodel/commands/AlgebraicCommand.cpp \
    viewmodel/commands/arteffectscommand.cpp \
    viewmodel/commands/BinaryMorphologyCommand.cpp \
    viewmodel/commands/channelcommand.cpp \
    viewmodel/commands/classiceffectscommand.cpp \
    viewmodel/commands/ClipCommand.cpp \
    viewmodel/commands/CurveCommand.cpp \
    viewmodel/commands/dualthresholdcommand.cpp \
    viewmodel/commands/edgedetectioncommand.cpp \
    viewmodel/commands/filtercommand.cpp \
    viewmodel/commands/GrayMorphologyCommand.cpp \
    viewmodel/commands/grayscaletransfercommand.cpp \
    viewmodel/commands/HistogramCommand.cpp \
    viewmodel/commands/houghcircledetectioncommand.cpp \
    viewmodel/commands/houghlinedetectioncommand.cpp \
    viewmodel/commands/huesaturalightcommand.cpp \
    viewmodel/commands/LevelCommand.cpp \
    viewmodel/commands/openfilecommand.cpp \
    viewmodel/commands/opensubdialogcommand.cpp \
    viewmodel/commands/opensubfilecommand.cpp \
    viewmodel/commands/otsucommand.cpp \
    viewmodel/commands/redocommand.cpp \
    viewmodel/commands/savefilecommand.cpp \
    viewmodel/commands/ScaleCommand.cpp \
    viewmodel/commands/undocommand.cpp \
    viewmodel/sinks/viewmodelsink.cpp \
    viewmodel/viewmodel.cpp



