!UTILS_PRI {
CONFIG += UTILS_PRI 

INCLUDEPATH += $$PWD/../

include(../Eigen/Eigen.pri)

HEADERS += \
    $$PWD/utils.h

SOURCES += \
    $$PWD/utils.cpp

}
