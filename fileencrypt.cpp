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

#include "fileencrypt.h"
#include "ui_fileencrypt.h"


FileEncrypt::FileEncrypt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileEncrypt)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    DragNDropEnabled = true;
    height = ui->imageLabel->height();
    width = ui->imageLabel->width();

    QObject::connect(this, SIGNAL(startEncryption()), this, SLOT(encrypt()));
    QObject::connect(this, SIGNAL(startDecryption()), this, SLOT(decrypt()));
    QObject::connect(this, SIGNAL(askPassword()), this, SLOT(getPassword()));

    reset();

    length = CryptFileDevice::kAesKeyLength256;
    minPasswordLength = 10;
    saltString = "192bitsalt22charencode";

    QIcon icon(":/Images/icon.icns");
    this->setWindowIcon(icon);
}

FileEncrypt::~FileEncrypt()
{
    delete ui;
}


void FileEncrypt::dragEnterEvent(QDragEnterEvent *ev)
{
    if(DragNDropEnabled){
        ev->accept();
        int h = height;
        int w = width;
        QPixmap pix(":Images/DropArrowImage.png");
        ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}


void FileEncrypt::dragLeaveEvent(QDragLeaveEvent *ev)
{
    if(DragNDropEnabled){
        ev->accept();
        int h = height/SmallRatio;
        int w = width/SmallRatio;
        QPixmap pix(":Images/DropArrowImage.png");
        ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}


void FileEncrypt::dropEvent(QDropEvent *ev)
{
    if(DragNDropEnabled){
        ev->accept();
        DragNDropEnabled = false;
        QList<QUrl> tmpL;
        tmpL = ev->mimeData()->urls();
        if(!tmpL.isEmpty() && !tmpL.at(0).toString().endsWith("/")){
            inputFileUrl = tmpL.at(0);
            inputFilePath = inputFileUrl.toString();
            inputFilePath = inputFilePath.remove(0,7);

            int h = height/SmallRatio;
            int w = width/SmallRatio;
            QPixmap pix(":Images/DropArrowImage.png");
            ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));

            ui->InstructionLabel->setText("Calculating...");

            this->repaint();
            QApplication::processEvents();

            emit askPassword();
        }
        else {
            int h = height/SmallRatio;
            int w = width/SmallRatio;
            QPixmap pix(":Images/DropArrowImage.png");
            ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void FileEncrypt::reset(){
    int h = height/SmallRatio;
    int w = width/SmallRatio;
    QPixmap pix(":Images/DropArrowImage.png");
    ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    inputFileUrl.clear();
    inputFilePath.clear();
    passwordInput.clear();
    DragNDropEnabled = true;
    ui->InstructionLabel->setText("Drag&Drop file to encrypt/decrypt");
    ui->destinationPathLine->clear();
}


void FileEncrypt::encrypt(){
    QFile file(inputFilePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "cannot open file";
    }

    CryptFileDevice cryptFileDevice;
    cryptFileDevice.setFileName(outputFilePath);
    cryptFileDevice.setPassword(QByteArray::fromStdString(passwordInput.toStdString()));
    cryptFileDevice.setSalt("application_salt");
    cryptFileDevice.setKeyLength(length);
    if (!cryptFileDevice.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "cannot open cryptor";
        file.close();
    }

    cryptFileDevice.write(file.readAll());

    file.close();
    cryptFileDevice.close();

    reset();
}

void FileEncrypt::decrypt(){
    CryptFileDevice cryptFileDevice(inputFilePath, QByteArray::fromStdString(passwordInput.toStdString()), "application_salt");
    cryptFileDevice.setKeyLength(length);

    if (!cryptFileDevice.open(QIODevice::ReadOnly))
    {
        qDebug() << "cannot open cryptor";
    }

    QFile file(outputFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "cannot open file";
        cryptFileDevice.close();
    }


    file.write(cryptFileDevice.readAll());


    cryptFileDevice.close();
    file.close();

    reset();
}


void FileEncrypt::on_strengthSelector_currentIndexChanged(int index)
{
    switch (index) {
    case 2:
        length = CryptFileDevice::kAesKeyLength128;
        minPasswordLength = 6;
        saltString = "128bitsalt";
        break;
    case 1:
        length = CryptFileDevice::kAesKeyLength192;
        minPasswordLength = 8;
        saltString = "192bitsalt16char";
        break;
    case 0:
        length = CryptFileDevice::kAesKeyLength256;
        minPasswordLength = 10;
        saltString = "192bitsalt22charencode";
        break;
    default:
        length = CryptFileDevice::kAesKeyLength256;
        minPasswordLength = 8;
        break;
    }
}

void FileEncrypt::on_destinationPathLine_textChanged(const QString &arg1)
{
    outputFilePath = arg1;
}

void FileEncrypt::getPassword()
{
    if(outputFilePath.isEmpty()){
        if(ui->modeSelector->currentText() == "Encrypt"){
            ui->destinationPathLine->setText(inputFilePath + ".enc");
            outputFilePath = inputFilePath + ".enc";
        } else{
            ui->destinationPathLine->setText(inputFilePath + ".dec");
            outputFilePath = inputFilePath + ".dec";
        }

        if(QFile(outputFilePath).exists()){
            QMessageBox msgBox;
            msgBox.setText("Replace file?");
            msgBox.setInformativeText("Destination file path not set. Using default path.\nDefault path file already exists, do you want to replace it?");
            msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int result = msgBox.exec();
            if(result == QMessageBox::Cancel | result == QMessageBox::Close){
                reset();
                return;
            }
        }
    }


    this->repaint();
    QApplication::processEvents();

    dialog = new PasswordInput(minPasswordLength);
    QObject::connect(dialog, SIGNAL(accepted()), this, SLOT(passwordInserted()));
    QObject::connect(dialog, SIGNAL(rejected()), this, SLOT(passwordRefused()));
    dialog->show();
}

void FileEncrypt::passwordInserted(){
    passwordInput = dialog->getPassword();

    this->repaint();
    QApplication::processEvents();

    if(ui->modeSelector->currentText() == "Encrypt"){
        emit startEncryption();
    } else{
        emit startDecryption();
    }
    delete dialog;
}

void FileEncrypt::passwordRefused(){
    reset();
    delete dialog;
}


void FileEncrypt::on_selectPathButton_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this,tr("Open Directory"), QDir::homePath());
    ui->destinationPathLine->setText(filepath);
}
