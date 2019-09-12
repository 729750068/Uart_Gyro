#-------------------------------------------------
#
# Project created by QtCreator 2019-06-14T16:40:12
#
#-------------------------------------------------

#QT       += core gui
#QT       += serialport
#QT       += concurrent
QT       += core gui printsupport serialport
QT       += concurrent
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prj_gyro_v1.6
TEMPLATE = app

DEFINES += "_X86_"

SOURCES += main.cpp\
        mainwindow.cpp \
    seralanalysis.cpp \
    canbusinterface.cpp

HEADERS  += mainwindow.h \
    seralanalysis.h \
    canbusinterface.h \
    ECanVci.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../gyroProcess/

#win32: LIBS += -L$$PWD/../../build-prj_gyro-Desktop_Qt_5_7_0_MSVC2013_32bit-Release/gyroProcess/release/ -lgyroProcess
#INCLUDEPATH += $$PWD/../../build-prj_gyro-Desktop_Qt_5_7_0_MSVC2013_32bit-Release/gyroProcess/release
#DEPENDPATH += $$PWD/../../build-prj_gyro-Desktop_Qt_5_7_0_MSVC2013_32bit-Release/gyroProcess/release

#32bit
win32: LIBS += -L$$PWD/lib/ -lECanVci
INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

