TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    host.cpp \
    hostlinux.cpp \
    hostwindows.cpp

HEADERS += \
    host.h \
    hostlinux.h \
    hostwindows.h

QMAKE_LFLAGS += -pthread
