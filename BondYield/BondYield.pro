TEMPLATE = app
TARGET = BondYield
DESTDIR = ../x64/Release
QT += core gui widgets
CONFIG += release
DEFINES += _UNICODE QT_DLL QT_WIDGETS_LIB
win32 {
    DEFINES += WIN64
}
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName)
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(BondYield.pri)
win32:RC_FILE = BondYield.rc
