TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../music.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../music.h

