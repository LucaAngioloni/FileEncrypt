/*
 * MIT License
 * 
 * Copyright (c) 2016 Luca Angioloni
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef FILEENCRYPT_H
#define FILEENCRYPT_H

#include <QMainWindow>
#include <QDropEvent>
#include <QUrl>
#include <QFile>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "cryptfiledevice.h"
#include "passwordinput.h"

#define SmallRatio 1.2

namespace Ui {
class FileEncrypt;
}

class FileEncrypt : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileEncrypt(QWidget *parent = 0);
    ~FileEncrypt();
public slots:
    void passwordInserted();
    void passwordRefused();
signals:
    void startEncryption();
    void startDecryption();
    void askPassword();

private slots:
    void encrypt();
    void decrypt();
    void on_strengthSelector_currentIndexChanged(int index);

    void on_destinationPathLine_textChanged(const QString &arg1);

    void getPassword();

    void on_selectPathButton_clicked();

private:
    Ui::FileEncrypt *ui;
    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);
    void dragLeaveEvent(QDragLeaveEvent *ev);
    void reset();
    QUrl inputFileUrl;
    QString inputFilePath;
    bool DragNDropEnabled;
    int height;
    int width;
    QString passwordInput;
    CryptFileDevice::AesKeyLength length;
    int minPasswordLength = 8;
    QString outputFilePath;
    PasswordInput* dialog;
    QString saltString;
};

#endif // FILEENCRYPT_H
