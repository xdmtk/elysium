QT       += core gui
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commandmanager.cpp \
    connectionprogresswindow.cpp \
    hyperlinkdiag.cpp \
    linkaction.cpp \
    main.cpp \
    ../core/CoreSettings.cpp \
    chatwindow.cpp \
    loginwindow.cpp \
    notificationmanager.cpp \
    profile.cpp \
    socketmanager.cpp \
    soundmanager.cpp

HEADERS += \
    ../core/CoreSettings.h \
    chatwindow.h \
    commandmanager.h \
    connectionprogresswindow.h \
    hyperlinkdiag.h \
    linkaction.h \
    loginwindow.h \
    portInfo.h \
    notificationmanager.h \
    profile.h \
    socketmanager.h \
    soundmanager.h

FORMS += \
    chatwindow.ui \
    connectionprogresswindow.ui \
    hyperlinkdiag.ui \
    loginwindow.ui \
    profile.ui

RC_ICONS = resources/appicon.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  resources.qrc
