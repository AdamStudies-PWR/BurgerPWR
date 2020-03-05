TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gamemaster.cpp \
        graphicfunc.cpp \
        interface.cpp \
        main.cpp

HEADERS += \
    gamemaster.h \
    graphicfunc.h \
    interface.h

INCLUDEPATH += -L/usr/lib/headers/
LIBS += -L/usr/lib -lncurses
LIBS += -pthread
