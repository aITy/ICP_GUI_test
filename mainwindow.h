#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QApplication>
#include <QList>


class GameBoard;
class ConnectDialog;

class MainWindow : public QMainWindow, Ui::MainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    MainWindow * getMainWindow() {
        return instance;
    }
    static MainWindow * getInstance();
    void addGame(GameBoard * );

protected:
    void closeEvent(QCloseEvent *);

private:
    void setupActions();

    QList<GameBoard*> games_arr;
    static MainWindow* instance;
private slots:
    void createLocalCpu();
    void createLocalVs();
    void createNetGame();
    void OpenFromFile();
    bool save();
    bool saveAs();
    bool saveAs(QString &);
    void close();
    void on_tabWidget_Games_tabCloseRequested(int index);

};

#endif // MAINWINDOW_H
