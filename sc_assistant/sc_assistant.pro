QT += quick
QT += widgets
TARGET=Assistant
ICON = icon.icns
RC_ICONS = icon.ico
CONFIG += qmltypes
QML_IMPORT_NAME = Sc_assitant.Backend
QML_IMPORT_MAJOR_VERSION = 1.0

CONFIG+=sdk_no_version_check

CONFIG += -static openssl-linked c++14

msvc:QMAKE_CFLAGS_RELEASE += /O2
msvc:QMAKE_CXXFLAGS_RELEASE += /O2

gcc:QMAKE_CFLAGS_RELEASE += -s -O2 -m32 -mtune=generic -fomit-frame-pointer
gcc:QMAKE_CXXFLAGS_RELEASE += -s -O2 -m32 -mtune=generic -fomit-frame-pointer -fno-exceptions
gcc:QMAKE_CXXFLAGS = -std=c++14
gcc:QMAKE_LFLAGS += -static-libgcc -static-libstdc++ --enable-stdcall-fixup -Wl,--enable-auto-import -Wl,--enable-runtime-pseudo-reloc

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
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    sc_assistant_ar_EG.qm

HEADERS += \
    backend.h \
    broadcastlistener.h \
    netclient.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
