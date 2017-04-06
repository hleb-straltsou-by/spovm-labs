TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tutor.cpp \
    tutorlinux.cpp

HEADERS += \
    tutor.h \
    tutorlinux.h

QMAKE_LFLAGS += -pthread

