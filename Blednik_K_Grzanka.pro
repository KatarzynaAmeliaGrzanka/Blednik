QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    car.cpp \
    intersection.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    movingobject.cpp \
    pedestrian.cpp \
    pedestrian_crossing.cpp \
    startwindow.cpp \
    traffic_lights.cpp \
    traffic_lights_controller.cpp

HEADERS += \
    Direction.h \
    car.h \
    intersection.h \
    mainwindow.h \
    map.h \
    movingobject.h \
    pedestrian.h \
    pedestrian_crossing.h \
    startwindow.h \
    traffic_lights.h \
    traffic_lights_controller.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
