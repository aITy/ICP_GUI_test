#include "gameboard.h"
#include "lightrock.h"
#include "darkrock.h"
//#include "rock.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

GameBoard::GameBoard(QWidget *parent)
        : QWidget(parent)
{
    setupUi(this);

    canvas = new QGraphicsScene();
    canvas->setSceneRect(70,65, graphicsView->width(), graphicsView->height());
    graphicsView->setScene(canvas);
    initGame();

    QList <QPair<QString, int> > str;
    str.append(QPair<QString, int>("a",0));
    this->lightenPossibleMoves(str);
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
                    DarkRock *pic = new DarkRock();
                    QGraphicsProxyWidget * widget = canvas->addWidget(pic);
                    QRectF pos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0, 50.0 ,50.0);
                    widget->setGeometry(pos);
                    pic->setPosition(pos);
                    dark_rocks.append(pic);
                }
            }
            else {
                if (j % 2 == 1) {
                    DarkRock *pic = new DarkRock();
                    QGraphicsProxyWidget * widget = canvas->addWidget(pic);
                    QRectF pos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0, 50.0 ,50.0);
                    widget->setGeometry(pos);
                    pic->setPosition(pos);
                    dark_rocks.append(pic);
                }
            }
        }
    }
    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i %2 == 0) {
                if (j % 2 == 1) {
                    LightRock *pic = new LightRock();
                    QGraphicsProxyWidget * widget = canvas->addWidget(pic);
                    QRectF pos(67.5 + j * 70.0 + 10.0, 70.0 + i * 70.0 + 10.0, 50.0 ,50.0);
                    widget->setGeometry(pos);
                    pic->setPosition(pos);
                    light_rocks.append(pic);
                }
            }
            else {
                if (j % 2 == 0) {
                    LightRock *pic = new LightRock();
                    QGraphicsProxyWidget * widget = canvas->addWidget(pic);
                    QRectF pos(67.5 + j * 70.0 + 10.0, 70.0 + i * 70.0 + 10.0, 50.0 ,50.0);
                    widget->setGeometry(pos);
                    pic->setPosition(pos);
                    light_rocks.append(pic);
                }
            }
        }
    }
}

QList<QRectF> GameBoard::convertCoords(QList<QPair<QString, int> >list) {
    // it�s expected, that int is in rage between 0 and 7
    QList<QRectF> ret;
    for (int i = 0; i < list.size(); i++) {
        int j = 0;
        QString str = "abcdefgh";
        QString::ConstIterator iter = str.begin();
        QPair<QString, int> item = list.at(i);
        while (iter != str.end()) {
            /*
            if (*iter == QChar(item.first)) {
                break;
            }
            */
            iter++; j++;
        }
        ret.append(QRectF(67.5 + item.second*70.0 + 10.0, 67.5 + (7-j) * 70 + 10, 50.0, 50.0));
    }
    return ret;
}

GameBoard::~GameBoard(){}

QPoint GameBoard::getItemCenterPos(int x, int y) {
    int pos_x, pos_y, space_x, space_y;
    int aux = 7;

    QList <QWidget> dark_pieces;

    for (int i = 9; i > 0; i--) {
        for (int j = 9; j > 0; j--) {
            //if (i > 9 && i % 9 != 0 && i % 2 == 0) {}
            gameGridLayout->getItemPosition((i*j) - aux - 1, &pos_x, &pos_y, &space_x, &space_y);
            aux--;
        }
        aux = 7;

    }

    //gameGridLayout->getItemPosition ( , &pos_x, &pos_y, &space_x, &space_y);
    QRect rect = gameGridLayout->cellRect(x,y);
    QPoint point = rect.topLeft();
    point.setX(point.x() + 35);
    point.setY(point.y() + 35);
    return point;
}

void GameBoard::changeItemContent(int x, int y) {
    /*
    QLayoutItem * item = gameGridLayout->itemAtPosition(x, y);
    qDebug() << "item geo" << item->geometry();
    QWidget *widget = item->widget();
    qDebug() << "geometry" << widget->geometry();
    QPainter* painter = new QPainter(widget);
    QLayout *layout = item->layout();
    QRectF target(QPoint(0.0, 0.0), QSize(50, 50));
    QRectF source(0.0, 0.0, 50, 50);
    QImage image(":/dark_piece.png");

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawImage(target, image, source);
    */

}

// QPair <a-h, 0-7>
void GameBoard::lightenPossibleMoves(QList<QPair<QString, int> >positions) {
    for (int i = 0; i < positions.size(); i++) {
        int j = 0;
        QString str = "abcdefgh";
        QString::ConstIterator iter = str.begin();
        QPair<QString, int> item = positions.at(i);
        while (iter != str.end()) {
            /*
            if (*iter == QChar(item.first)) {
                break;
            }
            */
            qDebug() << *iter;
            iter++; j++;
        }
        QLayoutItem *layout_item = gameGridLayout->itemAtPosition(7 - j, item.second);
        //QWidget * widget = layout_item->widget();
        //idget->setStyleSheet("background-color: rgba(227, 224, 119, 100)");
        possible_moves.append(positions.at(i));
    }

}

void GameBoard::hidePossibleMoves() {
    for (int i = 0; i < possible_moves.size(); i++) {
        int j = 0;
        QString str = "abcdefgh";
        QString::ConstIterator iter = str.begin();
        QPair<QString, int> item = possible_moves.at(i);
        while (iter != str.end()) {
            /*
            if (*iter == item.first) {
                break;
            }*/
            iter++; j++;
        }
        QLayoutItem *layout_item = gameGridLayout->itemAtPosition(j, 7 - item.second);
        QWidget * widget = layout_item->widget();
        widget->setStyleSheet("background-color: none");
        possible_moves.removeAt(i);
    }
}


