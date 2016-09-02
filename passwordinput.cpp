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
