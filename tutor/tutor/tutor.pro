TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread -lrt

SOURCES += main.cpp \
    tutor.cpp \
    tutor_linux.cpp \
    tutor_windows.cpp

HEADERS += \
    tutor.h \
    tutor_linux.h \
    tutor_windows.h

