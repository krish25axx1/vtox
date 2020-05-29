TARGET = v2x

QT = quickcontrols2 websockets





SOURCES = main.cpp 
   

CONFIG += link_pkgconfig

PKGCONFIG += libhomescreen qlibwindowmanager  libafbwsc

RESOURCES += \
    v2x.qrc 
    

include(app.pri)


