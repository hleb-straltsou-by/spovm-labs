TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread -lrt

SOURCES += main.cpp \
    student.cpp \
    student_linux.cpp \
    student_windows.cpp

HEADERS += \
    student.h \
    student_linux.h \
    student_windows.h

