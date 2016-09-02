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
