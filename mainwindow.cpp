#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"
#include "connectdialog.h"


#include <QCloseEvent>
#include <QFileDialog>
#include <QWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QStatusBar>
#include <QDebug>

MainWindow* MainWindow::instance = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    setWindowTitle(qApp->applicationName());
    setupActions();
}

MainWindow* MainWindow::getInstance() {
    if (!instance)
        instance = (MainWindow *) qApp->activeWindow();

    return instance;
}

void MainWindow::closeEvent(QCloseEvent * event) {
        QMessageBox::StandardButton choice;
        choice = QMessageBox::question(this,
                trUtf8("Opravdu ukoncit?"),
                trUtf8("Opravdu chcete ukoncit aplikaci '%1'?<br><b>Neulozene zmeny budou ztraceny!</b>").arg(qApp->applicationName()),
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No);

        if (choice == QMessageBox::Yes)
                event->accept();
        else
                event->ignore();
}

void MainWindow::setupActions() {
        // connects
        connect(action_NewLocalGame, SIGNAL(triggered()), this, SLOT(createLocalCpu()));
        connect(action_NewLocalGameVs, SIGNAL(triggered()), this, SLOT(createLocalVs()));
        connect(action_NewNetGame, SIGNAL(triggered()), this, SLOT(createNetGame()));
        connect(action_Open, SIGNAL(triggered()), this, SLOT(OpenFromFile()));
        connect(action_Save, SIGNAL(triggered()), this, SLOT(save()));
        connect(action_SaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
        connect(action_Close, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createLocalVs(){
    //Game *g = new Game(this);
    //QPoint point = game->getItemCenterPos(0,0);
    //QString test = QString::number(point.x()) + QString::number(point.y());
    GameBoard *b = new GameBoard();
    games_arr.append(b);
    QString str = trUtf8("Hra c.") + QString::number(games_arr.count());
    tabWidget_Games->addTab(b, str);
}

void MainWindow::createLocalCpu() {}

void MainWindow::createNetGame() {
    ConnectDialog *d = new ConnectDialog();
    d->exec();

}

void MainWindow::OpenFromFile(){
    QFileDialog openDialog(this);
    QString filename = openDialog.getOpenFileName(this, trUtf8("Open game open file"), "", "XML files(*.xml)");
    if (filename == NULL)
        return;

}

bool MainWindow::save(){
    /*
    if (filename.isEmpty())
        return saveAs();
    else
        return saveAs(filename);

    */
    return true;
}

bool MainWindow::saveAs(QString & filename) {
    return true;
}

bool MainWindow::saveAs() {
    QString fn = QFileDialog::getSaveFileName(NULL,
                                   trUtf8("Ulozit jako..."),
                                   QDir::homePath(),
                                   trUtf8("Soubory XML (%1)").arg("*.xml"));

    if (!fn.isEmpty())
    {
        //bool ok = saveAs(fn);
        //if (ok)
        //   filename = fn;
        //return ok;
        return true;
    }

    return false;
}

void MainWindow::close() {}

void MainWindow::on_tabWidget_Games_tabCloseRequested(int index)
{
    QMessageBox::StandardButton choice;
    choice = QMessageBox::question(this,
            trUtf8("Opravdu zavrit tuto hru?"),
            trUtf8("Opravdu chcete ukoncit hru '%1'?<br><b>Neulozene zmeny budou ztraceny!</b>").arg(tabWidget_Games->tabText(index)),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No);

    if (choice == QMessageBox::Yes)
            tabWidget_Games->removeTab(index);
    else
           return;
}

void MainWindow::addGame(GameBoard * board) {
    games_arr.append(board);
}

void MainWindow::setStatusMsg(const char * str) {
    myStatusBar->showMessage(QString(str), 2500);
}

void MainWindow::addMove(QPair<QString, int> src, QPair<QString, int> dest, QString type) {
    QString text = lineEdit_Moves->toPlainText();
    QString message = "";
    QPair<QPair< QPair<QString,int>, QPair<QString,int> > , QString> move;
    int i = 0;
    int counter = 0;
    while (i != text.length()) {
        if (text[i] == '\n')
            counter++;
        i++;
    }
    if (moves.count()%2 == 0)
        message += QString("%1. ").arg(QString::number(counter + 1));
    message += QString("%1%2").arg(QString(src.first)).arg(QString::number(src.second));
    if (type == "MOVE")
        message += " ";
    else
        message += "x";
    message += QString("%1%2").arg(QString(dest.first)).arg(QString::number(dest.second));
    if (moves.count()%2 == 0)
        message += "\t";
    else
        message += "\n";
    lineEdit_Moves->insertPlainText(message);
    move.first = QPair<QPair<QString, int>, QPair<QString,int> >(src, dest);
    move.second = QString(type);
    moves.append(move);
}

void MainWindow::clearMoves() {
    moves.clear();
    lineEdit_Moves->clear();
}
