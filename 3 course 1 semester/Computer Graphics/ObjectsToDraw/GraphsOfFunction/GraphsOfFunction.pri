!GRAPHSOFFUNCTION_PRI {
CONFIG += GRAPHSOFFUNCTION_PRI 

INCLUDEPATH += $$PWD/../

HEADERS += \
	$$PWD/grid.h

SOURCES += \
	$$PWD/grid.cpp

include(ParametricGraphOfFunction/ParametricGraphOfFunction.pri);
include(ExplicitGraphOfFunction/ExplicitGraphOfFunction.pri);
}
