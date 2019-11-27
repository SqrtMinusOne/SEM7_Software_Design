#-------------------------------------------------
#
# Project created by QtCreator 2019-11-24T20:11:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = L2
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

CONFIG += c++17

SOURCES += \
    adddialog.cpp \
    figures/atansegment.cpp \
    figures/pentagramtext.cpp \
    figures/text.cpp \
        main.cpp \
        mainwindow.cpp \
    graphwidget.cpp \
    figures/shape.cpp \
    figures/pentagram.cpp \
    point.cpp

HEADERS += \
    adddialog.h \
    exception.h \
    figures/atansegment.h \
    figures/pentagramtext.h \
    figures/text.h \
    hashMap.h \
        mainwindow.h \
    graphwidget.h \
    figures/shape.h \
    figures/pentagram.h \
    point.h

FORMS += \
        adddialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
