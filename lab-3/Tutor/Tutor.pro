TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tutor.cpp \
    tutorlinux.cpp \
    queue.cpp \
    studentsqueue.cpp \
    tutorwindows.cpp

HEADERS += \
    tutor.h \
    tutorlinux.h \
    queue.h \
    studentsqueue.h \
    tutorwindows.h

QMAKE_LFLAGS += -pthread

