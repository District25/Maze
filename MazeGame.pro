QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
=======
    algorithm.cpp \
    buttonview.cpp \
    gamecontroller.cpp \
    gamefactory.cpp \
    inputview.cpp \
>>>>>>> 9e7278f (Temporary commit - waiting to transfer updates to version-1.0 branch)
    main.cpp \
    mainwindow.cpp

HEADERS += \
<<<<<<< HEAD
    mainwindow.h
=======
    Coord.h \
    Observer.h \
    Subject.h \
    algorithm.h \
    buttonview.h \
    gamecontroller.h \
    gamefactory.h \
    inputview.h \
    mainwindow.h \
    maze.h \
    outputview.h
>>>>>>> 9e7278f (Temporary commit - waiting to transfer updates to version-1.0 branch)

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
