TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gamemaster.cpp \
        interface.cpp \
        main.cpp

HEADERS += \
    gamemaster.h \
    interface.h

INCLUDEPATH += -L/usr/lib/headers/
LIBS += -L/usr/lib -lncurses
