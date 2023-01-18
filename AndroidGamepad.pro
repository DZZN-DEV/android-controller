VERSION = 0.1.0

QT       += core gui network sensors

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += resources/darkstyle.qrc


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
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,x86_64) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

HEADERS += \
    src/dpadbutton.h \
    src/gamepad.h \
    src/gamepadbutton.h \
    src/gamepadellipsebutton.h \
    src/gamepadnamedbutton.h \
    src/gamepadrectbutton.h \
    src/joystick.h \
    src/mainwidget.h \
    src/mainwindow.h \
    src/settingswidget.h \
    src/util.h

SOURCES += \
    src/dpadbutton.cpp \
    src/gamepad.cpp \
    src/gamepadbutton.cpp \
    src/gamepadellipsebutton.cpp \
    src/gamepadnamedbutton.cpp \
    src/gamepadrectbutton.cpp \
    src/joystick.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/mainwindow.cpp \
    src/settingswidget.cpp
