!OBJECTSTODRAW_PRI {
CONFIG += OBJECTSTODRAW_PRI

INCLUDEPATH += $$PWD/../

include(ObjectToDraw/ObjectToDraw.pri);
include(Point3D/Point3D.pri)

include(Line3D/Line3D.pri)
include(GraphsOfFunction/GraphsOfFunction.pri)

include(ModelToDraw/ModelToDraw.pri)
}
