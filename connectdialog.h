#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "ui_connectdialog.h"

class ConnectDialog : public QDialog, private Ui::connectDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    QStringList dialogInfo;

public slots:
    void accept();

private:
    bool send();
};


#endif // CONNECTDIALOG_H
