QT += testlib core widgets

TEMPLATE = app
TARGET = OBJMTest

CONFIG += c++14 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle


SOURCES +=  tst_objectmanagertesting.cpp \
    ../../Game/basicinfo.cpp \
    ../../Game/buildings/hq.cpp \
    ../../Game/buildings/outpost.cpp \
    ../../Game/buildings/ranch.cc \
    ../../Game/buildings/upgradeablebuilding.cc \
    ../../Game/handlers/gameeventhandler.cc \
    ../../Game/mapwindow.cc \
    ../../Game/buildings/campus.cc \
    ../../Game/buildings/fishery.cc \
    ../../Game/buildings/market.cc \
    ../../Game/buildings/mine.cc \
    ../../Game/buildings/sawmill.cc \
    ../../Game/player.cc \
    ../../Game/startdialog.cc \
    ../../Game/tiles/sand.cpp \
    ../../Game/tiles/swamp.cpp \
    ../../Game/tiles/stone.cpp \
    ../../Game/tiles/water.cpp \
    ../../Game/handlers/objectmanager.cpp \
    ../../Game/graphics/worldscene.cpp \
    ../../Game/graphics/worlditem.cpp \
    ../../Game/graphics/gameview.cpp \
    ../../Game/workers/scout.cpp \
    ../../Game/workers/unitbase.cpp \
    ../../Game/workers/worker.cpp \
    ../../Game/tiles/forest.cpp \
    ../../Game/tiles/grassland.cpp \
    ../../Game/graphics/highlightitem.cpp \
    ../../Game/tiles/extendedtilebase.cpp

HEADERS += \
    ../../Game/basicinfo.hh \
    ../../Game/buildings/hq.hh \
    ../../Game/buildings/outpost.hh \
    ../../Game/buildings/ranch.hh \
    ../../Game/buildings/upgradeablebuilding.hh \
    ../../Game/exceptions/invalidcoordinate.hh \
    ../../Game/exceptions/lackingresources.hh \
    ../../Game/exceptions/movementlimitation.hh \
    ../../Game/handlers/gameeventhandler.hh \
    ../../Game/mapwindow.hh \
    ../../Game/buildings/campus.hh \
    ../../Game/buildings/fishery.hh \
    ../../Game/buildings/market.hh \
    ../../Game/buildings/mine.hh \
    ../../Game/buildings/sawmill.hh \
    ../../Game/player.hh \
    ../../Game/startdialog.hh \
    ../../Game/tiles/forest.h \
    ../../Game/tiles/sand.hh \
    ../../Game/tiles/swamp.hh \
    ../../Game/tiles/stone.hh \
    ../../Game/tiles/water.hh \
    ../../Game/handlers/objectmanager.hh \
    ../../Game/graphics/worldscene.h \
    ../../Game/graphics/worlditem.h \
    ../../Game/graphics/gameview.h \
    ../../Game/workers/scout.hh \
    ../../Game/workers/unitbase.hh \
    ../../Game/workers/worker.hh \
    ../../Game/tiles/grassland.h \
    ../../Game/graphics/highlightitem.h \
    ../../Game/tiles/extendedtilebase.h \
    ../../Game/exceptions/graphicsexception.h

FORMS += \
    ../../Game/mapwindow.ui \
    ../../Game/startdialog.ui

DEPENDPATH += \
    $$PWD/../../Game/ \
    $$PWD/../../Course/CourseLib/

INCLUDEPATH += \
    $$PWD/../../Game/ \
    $$PWD/../../Course/CourseLib/

OTHER_FILES +=

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../../Course/CourseLib/ -lCourseLib \
