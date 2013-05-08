#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow* MainWindow::instance = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    setWindowTitle(qApp->applicationName());
    setupActions();
    myStatusBar->setStyleSheet("padding-bottom: 15px");

    server = new QTcpServer(this);
    /** we will react on new connections in a user-loop */
    connect(server, SIGNAL(newConnection()), this, SLOT(gotConnection()));

    /** listen on all interfaces; set "random" port (everything else has default values - e.g. max connections 30) */
    if (! server->listen(QHostAddress::Any, 0)) {
        setStatusMsg("ERR: TCP server not listening.");
    }
    else {
        setStatusMsg(QString("server running on port ") + QString::number(server->serverPort()));
    }
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
        connect(action_Open, SIGNAL(triggered()), this, SLOT(openFromFile()));
        connect(action_OpenReplay, SIGNAL(triggered()), this, SLOT(openReplayFromFile()));
        connect(action_SaveIcp, SIGNAL(triggered()), this, SLOT(saveIcp()));
        connect(action_SaveXml, SIGNAL(triggered()), this, SLOT(saveXml()));
        connect(action_Help, SIGNAL(triggered()), this, SLOT(help()));
}

void MainWindow::createLocalVs(){
    Game *g = new Game(server);
    g->gameLocal();

    if (g->getError().isEmpty()) {
    //QPoint point = game->getItemCenterPos(0,0);
    //QString test = QString::number(point.x()) + QString::number(point.y());
        GameBoard *b = new GameBoard(g);
        this->addGame(b);
        QString str = trUtf8("Hra c.") + QString::number(games_arr.count());
        tabWidget_Games->addTab(b, str);
        tabWidget_Games->setCurrentIndex(tabWidget_Games->count() - 1);
    }
    else {
        setStatusMsg(g->getError());
    }
}

void MainWindow::createLocalCpu() {
    Game *g = new Game(server);
    //g->gameLocal(true, true);
}

void MainWindow::createNetGame() {
    d = new ConnectDialog();
    connect(d, SIGNAL(accepted()), this, SLOT(newNetworkGame()));
    d->exec();

}

void MainWindow::openFromFile(){
    QFileDialog openDialog(this);
    QString filename = openDialog.getOpenFileName(this, trUtf8("Open game from file"), "", "XML | ICP files(*.xml *.*)");
    if (filename == NULL)
        return;
    Game *g = new Game(server);

    if (g->gameFromFile(filename, Player::COLOR_DONT_KNOW)) {
        GameBoard *b = new GameBoard(g);
        this->addGame(b);
        QString str = trUtf8("Hra c.") + QString::number(games_arr.count());
        tabWidget_Games->addTab(b, str);
        tabWidget_Games->setCurrentIndex(tabWidget_Games->count() - 1);
        b->refresh();
    }
    else {
        setStatusMsg(g->getError());
    }

}

void MainWindow::openReplayFromFile() {
    QFileDialog openDialog(this);
    QString filename = openDialog.getOpenFileName(this, trUtf8("Open replay from file"), "", "XML files(*.xml)");
    if (filename == NULL)
        return;
    Game *g = new Game(server);
    g->gameFromFile(filename);
    if (g->getError().isEmpty()) {

        GameBoard *b = new GameBoard(g);
        this->addGame(b);
        QString str = trUtf8("Hra c.") + QString::number(games_arr.count());
        tabWidget_Games->addTab(b, str);
        tabWidget_Games->setCurrentIndex(tabWidget_Games->count() - 1);
        toggleReplayButtons(g);
        MainWindow::setLineEditText(g->getIcpSyntaxStr(true));
        b->refresh();
    }
    else {
        setStatusMsg(g->getError());
    }

}

bool MainWindow::saveIcp() {
    QString fn = QFileDialog::getSaveFileName(NULL,
                                   trUtf8("Ulozit jako ICP syntax"),
                                   QDir::homePath(),
                                   trUtf8("Soubory ICP syntaxe (%1)").arg("*.*"));

    GameBoard *b = games_arr.at(tabWidget_Games->currentIndex());
    Game *g = b->getGame();
    if (!fn.isEmpty())
    {
        QFile f(fn);
        /** overwrite file */
        f.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream fs(&f);
        fs << g->getIcpSyntaxStr();
        return true;
    }

    return false;
}

bool MainWindow::saveXml() {
    QString fn = QFileDialog::getSaveFileName(NULL,
                                   trUtf8("Ulozit jako XML"),
                                   QDir::homePath(),
                                   trUtf8("Soubory XML (%1)").arg("*.xml"));

    GameBoard *b = games_arr.at(tabWidget_Games->currentIndex());
    Game *g = b->getGame();
    if (!fn.isEmpty())
    {
        QFile f(fn);
        /** overwrite file */
        f.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream fs(&f);
        fs << g->getXmlStr();
        // icp g->getIcpSyntaxStr()
        return true;
    }
    return false;
}

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
    moves_str.append(QPair<GameBoard*, QString>(board, lineEdit_Moves->toPlainText()));
    QString str = trUtf8("Hra c.") + QString::number(games_arr.count());
    tabWidget_Games->addTab(board, str);
    tabWidget_Games->setCurrentIndex(tabWidget_Games->count() - 1);
}

void MainWindow::setStatusMsg(const char * str) {
    myStatusBar->showMessage(QString(str), 2500);
}

void MainWindow::setStatusMsg(QString str) {
    myStatusBar->showMessage(str, 2500);
}


void MainWindow::setLineEditText(QString str) {
    lineEdit_Moves->setPlainText(str);
}

void MainWindow::clearMoves() {
    moves.clear();
    lineEdit_Moves->clear();
}

void MainWindow::on_tabWidget_Games_currentChanged(int index)
{
    if (index != -1) {
        lineEdit_Moves->setPlainText(games_arr.at(index)->lineedit_moves);
        Game * g = games_arr.at(index)->getGame();
        toggleReplayButtons(g);
    }
    else {
        lineEdit_Moves->setPlainText(" ");
    }
}

int MainWindow::getGamesCount() {
    return games_arr.count();
}

void MainWindow::on_pushButton_Stop_clicked()
{
    GameBoard * b = games_arr.at(tabWidget_Games->currentIndex());
    Game * g = b->getGame();
    g->replayMoveStop();
}

void MainWindow::on_pushButton_Play_clicked()
{
    GameBoard * b = games_arr.at(tabWidget_Games->currentIndex());
    Game * g = b->getGame();
    int time = spinBox_Delay->value();
    g->setReplayTimeout(time);
    g->replayMoveToggle();
}

void MainWindow::on_pushButton_Rewind_clicked()
{
    GameBoard * b = games_arr.at(tabWidget_Games->currentIndex());
    Game * g = b->getGame();
    int step = spinBox_MovesCount->value();
    g->replayMove(step, false);
}

void MainWindow::on_pushButton_Pause_clicked()
{
    GameBoard * b = games_arr.at(tabWidget_Games->currentIndex());
    Game * g = b->getGame();
    int time = spinBox_Delay->value();
    g->setReplayTimeout(time);
    g->replayMoveToggle();
}

void MainWindow::on_pushButton_Forward_clicked()
{
    GameBoard * b = games_arr.at(tabWidget_Games->currentIndex());
    Game * g = b->getGame();
    int step = spinBox_MovesCount->value();
    g->replayMove(step, true);
}

void MainWindow::on_spinBox_Delay_valueChanged(int)
{
    GameBoard * b = games_arr.at(tabWidget_Games->currentIndex());
    Game * g = b->getGame();
    int time = spinBox_Delay->value();
    g->setReplayTimeout(time);

}

void MainWindow::toggleReplayButtons(Game * g) {
    bool flag = g->isReplaying();
    pushButton_Stop->setEnabled(flag);
    pushButton_Play->setEnabled(flag);
    pushButton_Pause->setEnabled(flag);
    pushButton_Rewind->setEnabled(flag);
    pushButton_Forward->setEnabled(flag);
    spinBox_Delay->setEnabled(flag);
    spinBox_MovesCount->setEnabled(flag);
}

void MainWindow::help() {
    Help * dialog = new Help();
    dialog->show();
}

void MainWindow::gotConnection() {
    if (server->hasPendingConnections()) {
        Game *g = new Game(server);
        GameBoard *b = new GameBoard(g);
        this->addGame(b);
        QString str = trUtf8("Hra c.") + QString::number(games_arr.count());
        tabWidget_Games->addTab(b, str);
        tabWidget_Games->setCurrentIndex(tabWidget_Games->count() - 1);
        g->gameRemote(server->nextPendingConnection());
    }
}

void MainWindow::gotInviteSlot(Player::color_t, QString) {
    AcceptDialog * dialog = new AcceptDialog();
    connect(dialog, SIGNAL(accepted()), this, SLOT(invited()));
    dialog->exec();
}

void MainWindow::gotExitSlot() {
    setStatusMsg("disconnected from game");
}

void MainWindow::newNetworkGame() {
    Game * g = new Game(server);
    QHostAddress addr;
    addr.setAddress(d->dialogInfo.at(1));
    connect(g, SIGNAL(gotInvite(Player::color_t, QString)), this, SLOT(gotInviteSlot(Player::color_t,QString)));
    connect(g, SIGNAL(gotExit()), this, SLOT(gotExitSlot()));
    if ( !g->gameRemote(addr, d->dialogInfo.at(2).toInt(), Player::COLOR_WHITE)) {
        setStatusMsg(g->getError());
    }
}
