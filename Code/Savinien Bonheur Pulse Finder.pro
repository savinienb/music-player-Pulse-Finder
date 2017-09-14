#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T22:09:02
#
#-------------------------------------------------

QT += core gui
QT += widgets
QT += phonon

TARGET = untitled
TEMPLATE = app

#-------------------------------------------------------------------------------------
QT +=medianamespace
#QT += mobility multimediakit
CONFIG += mobility
#MOBILITY = multimedia                   #here you may need to write "QT += multimedia" if you run under windows
CONFIG += mobility
MOBILITY += sensors
#-------------------------------------------------------------------------------------

CONFIG += console


RESOURCES += \
    Metronome.qrc


SOURCES += main.cpp\
    mainwindow.cpp \
    mathrythm.cpp \
    fftmath.cpp \
    audioclass.cpp

HEADERS  += mainwindow.h \
    mathrythm.h \
    fftmath.h \
    audioclass.h

FORMS    += mainwindow.ui


