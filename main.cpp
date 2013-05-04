#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Draughts_2013");
    MainWindow w;
    w.show();
    return a.exec();
}
