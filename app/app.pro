TARGET = v2x
QT = quick qml aglextras quickcontrols2



SOURCES = main.cpp 
   

CONFIG += link_pkgconfig
PKGCONFIG += libhomescreen qlibwindowmanager qtffaw

RESOURCES += \
    v2x.qrc 
    

include(app.pri)


