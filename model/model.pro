#QT       += core gui network
QT -= gui
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = model
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked dep   recated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        application.cpp \
        car.cpp \
        communicator.cpp \
        heavyVehicle.cpp \
        heavyVehicleMechanic.cpp \
        lightVehicleMechanic.cpp \
        main.cpp \
        mechanic.cpp \
        mechanicSenior.cpp \
        statistics.cpp \
        tlightVehicle.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    application.h \
    car.h \
    communicator.h \
    heavyVehicle.h \
    heavyVehicleMechanic.h \
    lightVehicle.h \
    lightVehicleMechanic.h \
    mechanic.h \
    mechanicSenior.h \
    tstatistics.h

INCLUDEPATH += /usr/local/Cellar/libconfig/1.7.2/include/
LIBS += -L/usr/local/Cellar/libconfig/1.7.2/lib/ -lconfig++


