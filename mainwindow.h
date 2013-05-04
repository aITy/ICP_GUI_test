#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QApplication>
#include <QList>


class GameBoard;

class MainWindow : public QMainWindow, Ui::MainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    MainWindow * getMainWindow() {
        return instance;
    }
    static MainWindow * getInstance();

protected:
    void closeEvent(QCloseEvent *);

private:
    void setupActions();

    QList<GameBoard*> games_arr;
    static MainWindow* instance;
private slots:
    void createNew();
    void OpenFromFile();
    void save();
    void saveAs();
    void close();
};

#endif // MAINWINDOW_H
