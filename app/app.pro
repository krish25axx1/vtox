TARGET = v2x
QT = quick qml aglextras



SOURCES = main.cpp 
   

CONFIG += link_pkgconfig
PKGCONFIG += PKGCONFIG += libhomescreen qlibwindowmanager qtappfw

RESOURCES += \
    v2x.qrc 
    

include(app.pri)


