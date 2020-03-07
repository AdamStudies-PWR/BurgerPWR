TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        client.cpp \
        gamemaster.cpp \
        graphicfunc.cpp \
        interface.cpp \
        main.cpp \
        objects.cpp \
        worker.cpp

HEADERS += \
    client.h \
    gamemaster.h \
    graphicfunc.h \
    interface.h \
    objects.h \
    worker.h

INCLUDEPATH += -L/usr/lib/headers/
LIBS += -L/usr/lib -lncurses
LIBS += -pthread
