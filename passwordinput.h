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
