#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T22:57:42
#
# MIT License
#
# Copyright (c) 2016 Luca Angioloni
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
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
