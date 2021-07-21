QT += quick
QT += widgets
ICON = icon.icns

CONFIG += qmltypes
QML_IMPORT_NAME = Sc_assitant.Backend
QML_IMPORT_MAJOR_VERSION = 1.0

CONFIG+=sdk_no_version_check

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        backend.cpp \
        broadcastlistener.cpp \
        main.cpp \
        netclient.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    sc_assistant_ar_EG.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sc_assistant_ar_EG.qm

HEADERS += \
    backend.h \
    broadcastlistener.h \
    netclient.h
