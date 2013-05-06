#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPainter>
#include <QLayoutItem>
#include <QPaintEvent>
#include "mainwindow.h"
#include "ui_board.h"

class DarkRock;
class LightRock;
class Canvas;

class GameBoard : public QWidget, Ui::Form_Board
{
    Q_OBJECT
public:
    GameBoard(QWidget *parent = 0);
    ~GameBoard();
    QPoint getItemCenterPos(int, int);
    void changeItemContent(int, int);
    Canvas * canvas;
    void initGame();
    //QList GameBoard::getinitPositions();
    QList<QRectF> convertCoords(QList<QPair<QString, int> >list);
    void lightenPossibleMoves(QList<QPair<QString, int> >positions);
    void hidePossibleMoves();
    QString getFilename();
    void setFilename(QString & str);
private:
    QList <DarkRock *> dark_rocks;
    QList <LightRock *> light_rocks;
    QList <QPair<QString, int> > possible_moves;
    QString filename;
};

#endif // GAMEBOARD_H
