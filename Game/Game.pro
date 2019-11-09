TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    buildings/ranch.cc \
    buildings/upgradeablebuilding.cc \
    handlers/gameeventhandler.cc \
    main.cpp \
    mapwindow.cc \
    buildings/campus.cc \
    buildings/fishery.cc \
    buildings/market.cc \
    buildings/mine.cc \
    buildings/sawmill.cc \
    player.cc \
    startdialog.cc \
    tiles/sand.cpp \
    tiles/swamp.cpp \
    tiles/stone.cpp \
    tiles/water.cpp \
    handlers/objectmanager.cpp \
    graphics/worldscene.cpp \
    graphics/worlditem.cpp \
    graphics/gameview.cpp \
    workers/unitbase.cpp

HEADERS += \
    basicinfo.hh \
    buildings/ranch.hh \
    buildings/upgradeablebuilding.hh \
    handlers/gameeventhandler.hh \
    mapwindow.hh \
    buildings/campus.hh \
    buildings/fishery.hh \
    buildings/market.hh \
    buildings/mine.hh \
    buildings/sawmill.hh \
    player.hh \
    startdialog.hh \
    tiles/sand.hh \
    tiles/swamp.hh \
    tiles/stone.hh \
    tiles/water.hh \
    handlers/objectmanager.hh \
    graphics/worldscene.h \
    graphics/worlditem.h \
    graphics/gameview.h \
    workers/unitbase.hh

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    startdialog.ui
