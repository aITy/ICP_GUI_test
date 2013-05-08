#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPainter>
#include <QLayoutItem>
#include <QPaintEvent>
#include "ui_board.h"
#include "../share/game.h"

class DarkRock;
class LightRock;
class Canvas;
class MainWindow;

class GameBoard : public QWidget, Ui::Form_Board
{
    Q_OBJECT
public:

    GameBoard(Game *parent = 0);
    ~GameBoard();
    QPoint getItemCenterPos(int, int);
    void changeItemContent(int, int);
    Canvas * getScene(){ return canvas; }
    void initGame();
    Game * getGame() { return game; }
    void storeMove(uint, uint, uint, uint);
    bool compareWithLastState();
    //QList GameBoard::getinitPositions();
    QList<QRectF> convertCoords(QList<QPair<int, int> > );
    QList<QRectF> convertCoords(QList<QPair<QString, int> > );
    //QList<QPair<int, int> > convertCoords(QList<QPointF> );
    QList<QPair<uint, uint> > convertCoords(QList<QPointF> );
    QList<QPair<QString, int> > convertCoords(QList<QPointF>, QString );

    // convert to pixel format
    QPointF convertCoords(uint, uint );
    QList<QPointF> convertCoords(QList<QPair<uint, uint> > );
    QList<QPointF> convertCoords(QPair<uint, uint>, QPair<uint, uint>);
    QList<QPointF> convertCoords(QList<QPair<QString, uint> > );
    QList<QPointF> convertCoords(QPair<QString, uint> , QPair<QString, uint> );
    void lightenPossibleMoves(QList<QPair<QString, int> >);
    void lightenPossibleMoves(QList<QPair<int, int> >);
    void hidePossibleMoves();
    void removeRock(QPointF );
    void clearBoard();
    QString getFilename();
    void setFilename(QString & );

    QString lineedit_moves;
private:
    QList <DarkRock *> dark_rocks;
    QList <LightRock *> light_rocks;
    QList <QPair<QString, int> > possible_moves;
    QString filename;
    Canvas * canvas;
    Game * game;
    QVector< QVector<Game::men_t> > board;
    QVector< QVector<Game::men_t> > stored_board_state;
    int refreshed;
    QPair<uint,uint> stored_src;
    QPair<uint,uint> stored_dest;
public slots:
    void refresh();
    void showMoves(uint, uint);
    void sceneUpdate(uint srcx, uint srcy, uint destx, uint desty);
    void toutExpired();
};

#endif // GAMEBOARD_H
