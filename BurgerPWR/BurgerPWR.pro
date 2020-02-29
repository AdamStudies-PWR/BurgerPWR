TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        interface.cpp \
        main.cpp

HEADERS += \
    interface.h

INCLUDEPATH += -L/usr/lib/headers/
LIBS += -L/usr/lib -lncurses
