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
    APP/main.cpp \
    WINDOW/startpage.cpp \
    WINDOW/gamewindow.cpp \
    VIEWMODEL/sinks/swviewmodelsink.cpp \
    VIEWMODEL/swviewmodel.cpp \
    MODEL/swmodel.cpp \
    WINDOW/sinks/gamewindowprosink.cpp \
    WINDOW/sinks/gamewindowsetsink.cpp \
    VIEWMODEL/commands/layoutcommand.cpp \
    APP/app.cpp \
    APP/commands/startbuttoncommand.cpp \
    VIEWMODEL/commands/mousemovecommand.cpp \
    WINDOW/sinks/mousemovecommandsink.cpp \
    WINDOW/sinks/mainimagesink.cpp \
    WINDOW/mainview.cpp \
    VIEWMODEL/commands/openfilecommand.cpp \
    VIEWMODEL/sinks/viewmodelsink.cpp

HEADERS += \
    common/etlbase.h \
    WINDOW/startpage.h \
    WINDOW/gamewindow.h \
    VIEWMODEL/sinks/swviewmodelsink.h \
    VIEWMODEL/swviewmodel.h \
    MODEL/swmodel.h \
    common/SWMatrix.h \
    WINDOW/sinks/gamewindowprosink.h \
    WINDOW/sinks/gamewindowsetsink.h \
    VIEWMODEL/commands/layoutcommand.h \
    APP/app.h \
    APP/commands/startbuttoncommand.h \
    VIEWMODEL/commands/mousemovecommand.h \
    WINDOW/sinks/mousemovecommandsink.h \
    common/parameters.h \
    WINDOW/mainview.h \
    WINDOW/sinks/mainimagesink.h \
    VIEWMODEL/commands/openfilecommand.h \
    VIEWMODEL/viewmodel.h \
    VIEWMODEL/commands/savefilecommand.h \
    VIEWMODEL/sinks/viewmodelsink.h

FORMS += \
    WINDOW/startpage.ui \
    WINDOW/gamewindow.ui

CONFIG += c++17
