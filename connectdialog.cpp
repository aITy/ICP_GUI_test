#include "connectdialog.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

ConnectDialog::ConnectDialog(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);

    QRegExpValidator* portValidator = new QRegExpValidator(QRegExp("^\[0-9]{5}$"), this);
    LineEdit_Port->setValidator(portValidator);
}

void ConnectDialog::accept()
{
    if (send())
        QDialog::accept();
}

bool ConnectDialog::send()
{
    int port;

    QString ipaddress = LineEdit_Addr->text();
    QHostAddress address;
    if (!address.setAddress(ipaddress))
    {
        QMessageBox::critical(this,
                              trUtf8("Invalid IP address"),
                              trUtf8("Format IP adresy neni validni!"));
        LineEdit_Addr->setFocus();
        return false;
    }

    QString port_str = LineEdit_Port->text();
    if (LineEdit_Port->validator()->validate(port_str, port) != QValidator::Acceptable)
    {
        QMessageBox::critical(this,
                              trUtf8("Invalid password"),
                              trUtf8("Heslo nesmi� obsahovat mezery a interpunkci a musi� bzt v rozmezi� %1-%2 znaku!").arg(8).arg(16));
        LineEdit_Port->setFocus();
        return false;
    }
    dialogInfo << ipaddress << QString::number(port);
    return true;
}
