#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T22:57:42
#
# Copyright 2016 Luca Angioloni
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
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
