#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"
#include "connectdialog.h"


#include <QCloseEvent>
#include <QFileDialog>
#include <QWidget>
#include <QMessageBox>
#include <QDesktopServices>

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

void MainWindow::createLocalCpu(){
    GameBoard *game = new GameBoard();
    games_arr.append(game);
    QString str = trUtf8("Hra c.") + QString::number(games_arr.count());
    tabWidget_Games->addTab(game, str);
    //QPoint point = game->getItemCenterPos(0,0);
    //QString test = QString::number(point.x()) + QString::number(point.y());
    //lineEdit_Moves->insert(test);
}

void MainWindow::createLocalVs() {}

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
