/*
Copyright 2016 Luca Angioloni
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
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
