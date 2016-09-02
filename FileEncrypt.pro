#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T22:57:42
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11 console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileEncrypt
TEMPLATE = app

SOURCES += main.cpp\
        fileencrypt.cpp \
    cryptfiledevice.cpp \
    passwordinput.cpp

HEADERS  += fileencrypt.h \
    cryptfiledevice.h \
    passwordinput.h

FORMS    += fileencrypt.ui \
    passwordinput.ui

INCLUDEPATH += /usr/local/opt/openssl/include

LIBS    += -lssl
LIBS    += -lcrypto

LIBS    += -L"/usr/local/opt/openssl/lib"

RESOURCES += \
    images.qrc

ICON = icon.icns
