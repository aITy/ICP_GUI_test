#include "gameboard.h"
#include "lightrock.h"
#include "darkrock.h"
#include "canvas.h"
//#include "rock.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

GameBoard::GameBoard(QWidget *parent)
        : QWidget(parent)
{
    setupUi(this);

    canvas = new Canvas(this);
    canvas->setSceneRect(70,65, graphicsView->width(), graphicsView->height());
    graphicsView->setScene(canvas);
    initGame();

    /* TO DO FILENAME */

    //QList <QPair<QString, int> > str;
    //this->lightenPossibleMoves(str);
}
/*
QList GameBoard::getinitPositions() {

}
*/
void GameBoard::initGame(){

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if (i % 2 == 1) {
                if (j % 2 == 0) {
                    DarkRock *dark_rock = new DarkRock();
                    canvas->addItem(dark_rock);
                    dark_rock->setPos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0);
                    dark_rocks.append(dark_rock);
                }
            }
            else {
                if (j % 2 == 1) {
                    DarkRock *dark_rock = new DarkRock();
                    canvas->addItem(dark_rock);
                    dark_rock->setPos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0);
                    dark_rocks.append(dark_rock);
                }
            }
        }
    }
    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i %2 == 0) {
                if (j % 2 == 1) {
                    LightRock *light_rock = new LightRock();
                    canvas->addItem(light_rock);
                    light_rock->setPos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0);
                    light_rocks.append(light_rock);
                }
            }
            else {
                if (j % 2 == 0) {
                    LightRock *light_rock = new LightRock();
                    canvas->addItem(light_rock);
                    light_rock->setPos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0);
                    light_rocks.append(light_rock);
                }
            }
        }
    }
    /*
    qDebug() << dark_rocks.at(0)->scenePos();
    QList<QPointF>list;
    list.append(dark_rocks.at(0)->scenePos());
    QList<QPair<QString,int> > ret = convertCoords(list, QString("output"));
    qDebug() << ret;*/

}

void GameBoard::removeRock(QPointF position) {
    QPointF rock_pos;
    for (int i = 0; i < light_rocks.size(); i++) {
        rock_pos = light_rocks.at(i)->scenePos();
        if (rock_pos.x() == position.x() && rock_pos.y() == position.y()) {
            light_rocks.removeAt(i);
            return;
        }
    }
    for (int i = 0; i < dark_rocks.size(); i++) {
        rock_pos = dark_rocks.at(i)->scenePos();
        if (rock_pos.x() == position.x() && rock_pos.y() == position.y()) {
            dark_rocks.removeAt(i);
            return;
        }
    }
}

QList<QRectF> GameBoard::convertCoords(QList<QPair<int, int> >list) {
    // it´s expected, that int is in rage between 0 and 7
    QList<QRectF> ret;
    for (int i = 0; i < list.size(); i++) {
        QPair<int, int> item = list.at(i);
        QLayoutItem *layout_item = gameGridLayout->itemAtPosition(7 - item.second + 1, item.first + 1);
        ret.append(QRectF(layout_item->geometry().x(), layout_item->geometry().y(), 50, 50));
    }
    return ret;
}

 QList<QPair<int,int> >GameBoard::convertCoords(QList<QPointF> list) {

    QList<QPair<int,int> > ret;
    for (int i = 0; i < list.size(); i++) {
        QPointF pos = list.at(i);
        int x = (pos.x() - 10 - 67.5)/70;
        int y = (pos.y() - 10 - 67.5)/70;

        ret.append(QPair<int,int>(x,7 - y));
    }
    return ret;
}

 QList<QPair<QString,int> >GameBoard::convertCoords(QList<QPointF> list, QString str) {

    QList<QPair<QString,int> > ret;
    QString chars = "abcdefgh";
    QString ch;
    for (int i = 0; i < list.size(); i++) {
        QPointF pos = list.at(i);
        int x = (pos.x() - 10 - 67.5)/70;
        int y = (pos.y() - 10 - 67.5)/70;

        for (int j = 0; j <= x; j++) {
            ch = QString(chars[j]);
        }
        if (str == "output")
            ret.append(QPair<QString, int>(ch,8 - y));
        else
            ret.append(QPair<QString, int>(ch,8 - y));
    }
    return ret;
}

QList<QRectF> GameBoard::convertCoords(QList<QPair<QString, int> >list) {
    // it´s expected, that int is in rage between 0 and 7
    QList<QRectF> ret;
    int j = 0;
    for (int i = 0; i < list.size(); i++) {
        QString str = "abcdefgh";
        QString::ConstIterator iter = str.begin();
        QPair<QString, int> item = list.at(i);

        while (iter != str.end()) {
            if (*iter == QChar(item.first[0])) {
                break;
            }
            iter++; j++;
        }
        ret.append(QRectF(67.5 + item.second*70.0 + 10.0, 67.5 + (7-j) * 70 + 10, 50.0, 50.0));
    }
    return ret;
}

GameBoard::~GameBoard(){}

// QPair <a-h, 0-7>
/*  _ _ _ _ _ _ _ _
  7|               |
  6|               |
  5|               |
  4|               |
  3|               |
  2|               |
  1|               |
  0|_ _ _ _ _ _ _ _|
    a b c d e f g h
*/
void GameBoard::lightenPossibleMoves(QList<QPair<QString, int> >positions) {
    for (int i = 0; i < positions.size(); i++) {
        int j = 0;
        QString str = "abcdefgh";
        QString::ConstIterator iter = str.begin();
        QPair<QString, int> item = positions.at(i);
        QString pos_x = item.first;
        int pos_y = item.second;

        while (iter != str.end()) {
            if (*iter == QChar(pos_x[0])) {
                break;
            }
            iter++; j++;
        }
        QLayoutItem *layout_item = gameGridLayout->itemAtPosition(7 - pos_y + 1, j + 1);
        //qDebug() << layout_item->geometry();
        QWidget * widget = layout_item->widget();
        widget->setStyleSheet("background-color: rgba(227, 224, 119, 100)");
        possible_moves.append(positions.at(i));
    }
}
// QPair <0.7, 0-7>
/*  _ _ _ _ _ _ _ _
  7|               |
  6|               |
  5|               |
  4|               |
  3|               |
  2|               |
  1|               |
  0|_ _ _ _ _ _ _ _|
    0 1 2 3 4 5 6 7
*/
void GameBoard::lightenPossibleMoves(QList<QPair<int, int> >positions) {
    QString str = "abcdefg";
    for (int i = 0; i < positions.size(); i++) {
        QPair<int, int> item = positions.at(i);

        QLayoutItem *layout_item = gameGridLayout->itemAtPosition(7 - item.second + 1, item.first + 1);
        //qDebug() << layout_item->geometry();
        QWidget * widget = layout_item->widget();
        widget->setStyleSheet("background-color: rgba(227, 224, 119, 100)");
        possible_moves.append(QPair<QString, int>(QString(str[item.first]), item.second));
    }

}

void GameBoard::hidePossibleMoves() {
    for (int i = 0; i < possible_moves.size(); i++) {
        int j = 0;
        QString str = "abcdefgh";
        QString::ConstIterator iter = str.begin();
        QPair<QString, int> item = possible_moves.at(i);
        QString pos_x = item.first;
        int pos_y = item.second;

        while (iter != str.end()) {
            if (*iter == QChar(pos_x[0])) {
                break;
            }
            iter++; j++;
        }
        QLayoutItem *layout_item = gameGridLayout->itemAtPosition(7 - pos_y + 1, j + 1);
        QWidget * widget = layout_item->widget();
        widget->setStyleSheet("background-color:rgb(0, 0, 0)");
        possible_moves.removeAt(i);
    }
}


