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

SOURCES += \
    common/util.cpp \
    app/main.cpp \
    app/app.cpp \
#    app/commands/startbuttoncommand.cpp \
#    view/startpage.cpp \
#    view/gamewindow.cpp \
    view/mainview.cpp \
#    view/sinks/gamewindowprosink.cpp \
#    view/sinks/gamewindowsetsink.cpp \
#    view/sinks/mousemovecommandsink.cpp \
    view/sinks/mainimagesink.cpp \
#    viewmodel/swviewmodel.cpp \
#    viewmodel/commands/layoutcommand.cpp \
#    viewmodel/commands/mousemovecommand.cpp \
    viewmodel/commands/openfilecommand.cpp \
#    viewmodel/sinks/swviewmodelsink.cpp \
    viewmodel/sinks/viewmodelsink.cpp \
#    model/swmodel.cpp \
    model/model.cpp \
#    model/methods/crop_image.cpp \
    model/methods/open_file.cpp \
    model/methods/reset.cpp \
    model/methods/save_file.cpp \
    viewmodel/viewmodel.cpp \
    viewmodel/commands/savefilecommand.cpp

HEADERS += \
    common/etlbase.h \
#    common/SWMatrix.h \
    common/type.h \
    common/util.h \
    common/parameters.h \
#    view/startpage.h \
#    view/gamewindow.h \
    view/mainview.h \
    view/sinks/mainimagesink.h \
#    view/sinks/mousemovecommandsink.h \
#    view/sinks/gamewindowprosink.h \
#    view/sinks/gamewindowsetsink.h \
    app/app.h \
#    app/commands/startbuttoncommand.h \
    viewmodel/commands/savefilecommand.h \
#    viewmodel/commands/layoutcommand.h \
#    viewmodel/commands/mousemovecommand.h \
    viewmodel/commands/openfilecommand.h \
#    viewmodel/swviewmodel.h \
    viewmodel/viewmodel.h \
#    viewmodel/sinks/swviewmodelsink.h \
    viewmodel/sinks/viewmodelsink.h \
#    model/swmodel.h \
    model/model.h

FORMS +=
# \
#    view/startpage.ui \
#    view/gamewindow.ui

CONFIG += c++17
