!SYSTEM_PRI {
CONFIG += SYSTEM_PRI 

INCLUDEPATH += $$PWD/../

include(../utils/utils.pri)

HEADERS += \
    $$PWD/system.h

SOURCES += \
    $$PWD/system.cpp

}
