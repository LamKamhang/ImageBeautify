#-------------------------------------------------
#
# Project created by QtCreator 2018-07-13T08:20:58
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myMainWindow
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


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    tools.h \
    imagecontainer.h \

FORMS += \
        mainwindow.ui

#DISTFILES +=
#INCLUDEPATH += /usr/local/include
#LIBS += -L/usr/local/Cellar/opencv/3.4.1_2/lib/ -lopencv_imgproc
#LIBS += -L/usr/local/Cellar/opencv/3.4.1_2/lib/ -lopencv_core
#LIBS += -L/usr/local/Cellar/opencv/3.4.1_2/lib/ -lopencv_highgui
#LIBS += -L/usr/local/Cellar/opencv/3.4.1_2/lib/ -lopencv_imgcodecs
DISTFILES +=
INCLUDEPATH += E:/"Visual Studio 2017"/OpenCV/opencv/opencv/build/include
LIBS += -LE:/"Visual Studio 2017"/OpenCV/opencv/opencv/build/x64/vc15/lib -lopencv_world341
LIBS += -LE:/"Visual Studio 2017"/OpenCV/opencv/opencv/build/x64/vc15/bin -lopencv*.lib
LIBS += -LE:/"Visual Studio 2017"/OpenCV/opencv/opencv/build/x64/vc15/bin -lopencv*.dll

RESOURCES += \
    imagerc.qrc

