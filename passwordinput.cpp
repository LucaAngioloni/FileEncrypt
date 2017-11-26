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

#include "passwordinput.h"
#include "ui_passwordinput.h"

#include <QMessageBox>

PasswordInput::PasswordInput(int minLength, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordInput)
{
    ui->setupUi(this);
    this->minLength = minLength;
    ui->password1->setEchoMode(QLineEdit::Password);
    ui->password1->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->password2->setEchoMode(QLineEdit::Password);
    ui->password2->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

    this->repaint();
    QApplication::processEvents();
}

PasswordInput::~PasswordInput()
{
    delete ui;
}


void PasswordInput::on_cancelButton_clicked()
{
    emit reject();
}


void PasswordInput::on_okButton_clicked()
{
    if(ui->password1->text() == ui->password2->text()){
        if(ui->password1->text().length() >= minLength){
            password = ui->password1->text();
            emit accept();
        } else {
            QMessageBox msgBox;
            msgBox.setText("Password Error");
            msgBox.setInformativeText("Password is too short.\nHas to be at least " + QString::number(minLength) + " characters long");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            ui->password1->clear();
            ui->password2->clear();
        }
    } else{
        QMessageBox msgBox;
        msgBox.setText("Password Error");
        msgBox.setInformativeText("Password repeated doesn't match");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        ui->password1->clear();
        ui->password2->clear();
    }
}
