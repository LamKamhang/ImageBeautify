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

HEADERS += \
    app/app.h \
    common/etlbase.h \
    common/parameters.h \
    common/type.h \
    common/util.h \
    model/filters/art_effect.h \
    model/imageoperation/aux_image_alg.h \
    model/logoperation/aux_log_alg.h \
    model/model.h \
    view/sinks/maincommandsink.h \
    view/sinks/mainimagesink.h \
    view/algebraicdialog.h \
    view/binarymorphologydialog.h \
    view/clickableqlabel.h \
    view/clipbox.h \
    view/clipdialog.h \
    view/curvecanvas.h \
    view/curvedialog.h \
    view/dualthresholddialog.h \
    view/edgedetectiondialog.h \
    view/filterdialog.h \
    view/graymorphologydialog.h \
    view/histogramdialog.h \
    view/histogramview.h \
    view/houghcircledetectiondialog.h \
    view/huesaturalightdialog.h \
    view/leveldialog.h \
    view/mainview.h \
    view/scaledialog.h \
    view/specialeffectdialog.h \
    view/structureelementcanvas.h \
    viewmodel/commands/AlgebraicCommand.h \
    viewmodel/commands/arteffectscommand.h \
    viewmodel/commands/BinaryMorphologyCommand.h \
    viewmodel/commands/channelcommand.h \
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
    model/imageoperation/aux_image_alg.cpp \
    model/imageoperation/imageoperation.cpp \
    model/logoperation/aux_log_alg.cpp \
    model/logoperation/logoperation.cpp \
    model/model.cpp \
    view/sinks/maincommandsink.cpp \
    view/sinks/mainimagesink.cpp \
    view/algebraicdialog.cpp \
    view/binarymorphologydialog.cpp \
    view/clickableqlabel.cpp \
    view/clipbox.cpp \
    view/clipdialog.cpp \
    view/curvecanvas.cpp \
    view/curvedialog.cpp \
    view/dualthresholddialog.cpp \
    view/edgedetectiondialog.cpp \
    view/filterdialog.cpp \
    view/graymorphologydialog.cpp \
    view/histogramdialog.cpp \
    view/histogramview.cpp \
    view/houghcircledetectiondialog.cpp \
    view/huesaturalightdialog.cpp \
    view/leveldialog.cpp \
    view/mainview.cpp \
    view/scaledialog.cpp \
    view/specialeffectdialog.cpp \
    view/structureelementcanvas.cpp \
    viewmodel/commands/AlgebraicCommand.cpp \
    viewmodel/commands/arteffectscommand.cpp \
    viewmodel/commands/BinaryMorphologyCommand.cpp \
    viewmodel/commands/channelcommand.cpp \
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


