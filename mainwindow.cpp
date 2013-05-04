#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"


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
        connect(action_NewLocalGame, SIGNAL(triggered()), this, SLOT(createNew()));
        connect(action_Open, SIGNAL(triggered()), this, SLOT(OpenFromFile()));
        connect(action_Save, SIGNAL(triggered()), this, SLOT(save()));
        connect(action_SaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
        connect(action_Close, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createNew(){
    GameBoard *game = new GameBoard();
    games_arr.append(game);
    QString str = trUtf8("Hra c.") + QString::number(games_arr.count());
    tabWidget_Games->addTab(game, str);
    //QPoint point = game->getItemCenterPos(0,0);
    //QString test = QString::number(point.x()) + QString::number(point.y());
    //lineEdit_Moves->insert(test);
}

void MainWindow::OpenFromFile(){}

void MainWindow::save(){}

void MainWindow::saveAs() {}

void MainWindow::close() {
}
