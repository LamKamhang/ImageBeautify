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

#LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_highgui.dylib \
#        /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_core.dylib \
#        /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_imgproc.dylib \
#        /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_imgcodecs.dylib \
#        /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_*.dylib

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
    model/imageoperation/aux_image_alg.h \
    model/model.h \
    view/sinks/mainimagesink.h \
    view/edgedetectiondialog.h \
    view/filterdialog.h \
    view/houghcircledetectiondialog.h \
    view/mainview.h \
    viewmodel/commands/channelcommand.h \
    viewmodel/commands/edgedetectioncommand.h \
    viewmodel/commands/filtercommand.h \
    viewmodel/commands/houghcircledetectioncommand.h \
    viewmodel/commands/openfilecommand.h \
    viewmodel/commands/savefilecommand.h \
    viewmodel/sinks/viewmodelsink.h \
    viewmodel/viewmodel.h

SOURCES += \
    app/app.cpp \
    app/main.cpp \
    common/util.cpp \
    model/imageoperation/aux_image_alg.cpp \
    model/imageoperation/imageoperation.cpp \
    model/model.cpp \
    view/sinks/mainimagesink.cpp \
    view/edgedetectiondialog.cpp \
    view/filterdialog.cpp \
    view/houghcircledetectiondialog.cpp \
    view/mainview.cpp \
    viewmodel/commands/channelcommand.cpp \
    viewmodel/commands/edgedetectioncommand.cpp \
    viewmodel/commands/filtercommand.cpp \
    viewmodel/commands/houghcircledetectioncommand.cpp \
    viewmodel/commands/openfilecommand.cpp \
    viewmodel/commands/savefilecommand.cpp \
    viewmodel/sinks/viewmodelsink.cpp \
    viewmodel/viewmodel.cpp
