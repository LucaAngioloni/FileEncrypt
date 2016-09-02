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

#ifndef PASSWORDINPUT_H
#define PASSWORDINPUT_H

#include <QDialog>

namespace Ui {
class PasswordInput;
}

class PasswordInput : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordInput(int minLength, QWidget *parent = 0);
    ~PasswordInput();
    QString getPassword(){
        return password;
    }

private slots:

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::PasswordInput *ui;
    QString password;
    int minLength;
};

#endif // PASSWORDINPUT_H
