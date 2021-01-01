!VIEWPORT_PRI {
CONFIG += VIEWPORT_PRI 

INCLUDEPATH += $$PWD/../

include(../ObjectsToDraw/ObjectsToDraw.pri)
include(../Camera/Camera.pri)

HEADERS += \
    $$PWD/viewport.h

SOURCES += \
    $$PWD/viewport.cpp

}
