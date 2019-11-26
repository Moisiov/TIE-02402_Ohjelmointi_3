QT += testlib
QT += core gui widgets

CONFIG += c++14 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_gameeventhandlertesting.cpp

DEPENDPATH += \
    $$PWD/../../Game \
    $$PWD/../../Game/handler \
    $$PWD/../../Course/CourseLib

INCLUDEPATH += \
    $$PWD/../../Game \
    $$PWD/../../Game/handlers \
    $$PWD/../../Course/CourseLib
