TARGET = v2x
QT = quick qml aglextras



SOURCES = main.cpp 
   

CONFIG += link_pkgconfig
PKGCONFIG += qtappfw

RESOURCES += \
    v2x.qrc 
    

include(app.pri)


