#include "gameboard.h"
#include "lightrock.h"
#include "darkrock.h"
#include "canvas.h"
#include "mainwindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QMessageBox>

GameBoard::GameBoard(Game *parent)
        : game(parent)
{
    setupUi(this);

    canvas = new Canvas(this);
    canvas->setSceneRect(70,65, graphicsView->width(), graphicsView->height());
    graphicsView->setScene(canvas);
    initGame();
    refreshed = 0;

    connect(game, SIGNAL(refresh()), this, SLOT(refresh()));
    connect(canvas, SIGNAL(showPossibleMoves(uint,uint)), this, SLOT(showMoves(uint, uint)));
    connect(canvas, SIGNAL(sceneUpdated(uint,uint,uint,uint)), this, SLOT(sceneUpdate(uint, uint, uint, uint)));

    /* TO DO FILENAME */

    //QList <QPair<QString, int> > str;
    //this->lightenPossibleMoves(str);
}
/*
QList GameBoard::getinitPositions() {

}
*/
void GameBoard::initGame(){

    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i %2 == 0) {
                if (j % 2 == 1) {
                    DarkRock *dark_rock = new DarkRock();
                    canvas->addItem(dark_rock);
                    dark_rock->setPos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0);
                    dark_rocks.append(dark_rock);
                }
            }
            else {
                if (j % 2 == 0) {
                    DarkRock *dark_rock = new DarkRock();
                    canvas->addItem(dark_rock);
                    dark_rock->setPos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0);
                    dark_rocks.append(dark_rock);
                }
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if (i % 2 == 1) {
                if (j % 2 == 0) {
                    LightRock *light_rock = new LightRock();
                    canvas->addItem(light_rock);
                    light_rock->setPos(67.5 + j * 70.0 + 10.0, 67.5 + i * 70.0 + 10.0);
                    light_rocks.append(light_rock);
                }
            }
            else {
                if (j % 2 == 1) {
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
            if (light_rocks.count() == 0) {
                // black player win
                QMessageBox::information(this, "Black player won", "Cerny hrac vyhral!");
            }
            return;
        }
    }
    for (int i = 0; i < dark_rocks.size(); i++) {
        rock_pos = dark_rocks.at(i)->scenePos();
        if (rock_pos.x() == position.x() && rock_pos.y() == position.y()) {
            dark_rocks.removeAt(i);
            if (dark_rocks.count() == 0) {
                // black player win
                QMessageBox::information(this, "White player won", "Bily hrac vyhral!");
            }
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

QList<QPair<uint,uint> > GameBoard::convertCoords(QList<QPointF> list) {

    QList<QPair<uint,uint> > ret;
    for (int i = 0; i < list.size(); i++) {
        QPointF pos = list.at(i);
        uint x = (pos.x() - 10 - 67.5)/70;
        uint y = (pos.y() - 10 - 67.5)/70;

        ret.append(QPair<uint,uint>(x + 1,y + 1));
    }
    return ret;
}

/*
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
*/
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
            ret.append(QPair<QString, int>(ch,y));
        else
            ret.append(QPair<QString, int>(ch,y));
    }
    return ret;
}

/**
 * Convert coordinates from <a..h,1..8> format to coordinates of rectangle, size of rectangle is 70x70
 * @param coordinates in <a..h,1..8> format
 * @return Return list of positions of rocks as list of QRectF
 */
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
        ret.append(QRectF(67.5 + item.second*70.0 + 10.0, 67.5 + j * 70 + 10, 50.0, 50.0));
    }
    return ret;
}


/**
 * Convert coordinates from <1..8,1..8> format to pixel coordinates format, size of array is 70x70
 * @param coordinates in <1..8,1..8> format
 * @return Return the center of array in pixel coordinates
 */
QList<QPointF> GameBoard::convertCoords(QList<QPair<uint, uint> > list){
    QList<QPointF> ret;
    double x,y;

    for (int i = 0; i < list.size(); i++) {
        QPair<uint, uint> item = list.at(i);
        // multiply position by size of array and shift to center of array
        x = item.first*70 + 35;
        y = item.second*70 + 35;

        ret.append(QPointF(x, y));
    }
    return ret;
};

QPointF GameBoard::convertCoords(uint x, uint y){
    return QPointF(x*70 + 10, y*70 + 10);
};

QList<QPointF> GameBoard::convertCoords(QPair<uint, uint> src, QPair<uint, uint> dest){
    QList<QPointF> ret;

    // multiply position by size of array and shift to center of array
    ret.append(QPointF(src.first*70 + 35, src.second*70 + 35));
    ret.append(QPointF(dest.first*70 + 35, dest.second*70 + 35));

    return ret;
};

/**
 * Convert coordinates from <a..h,1..8> format to pixel coordinates, size of array is 70x70
 * @param coordinates in <a..h,1..8> format
 * @return Return the center of array in pixel coordinates
 */
QList<QPointF> GameBoard::convertCoords(QList<QPair<QString, uint> > list){
    QList<QPointF> ret;
    QString str = "abcdefgh";
    double item_to_number, x, y;

    for (int i = 0; i < list.size(); i++) {
        QPair<QString, uint> item = list.at(i);
        // convert a..h to 1..8
        item_to_number = 1 + double(str.indexOf(item.first));
        // multiply position by size of array and shift to center of array
        x = item_to_number*70 + 35;
        y = item.second*70 + 35;

        ret.append(QPointF(x, y));
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
    /*
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
    }*/
}
// QPair <0.7, 0-7>
/*  _ _ _ _ _ _ _ _
  1|               |
  2|               |
  3|               |
  4|               |
  5|               |
  6|               |
  7|               |
  8|_ _ _ _ _ _ _ _|
    1 2 3 4 5 6 7 8
*/
void GameBoard::lightenPossibleMoves(QList<QPair<int, int> >positions) {
    QString str = "abcdefgh";
    for (int i = 0; i < positions.count(); i++) {
        QPair<int, int> item = positions.at(i);

        QLayoutItem *layout_item = gameGridLayout->itemAtPosition(item.first + 1, item.second + 1);
        qDebug() << layout_item->geometry();
        QWidget * widget = layout_item->widget();
        widget->setStyleSheet("background-color: rgba(227, 224, 119, 100)");
        possible_moves.append(QPair<QString, int>(QString(str[item.first]), item.second));
    }

}

void GameBoard::hidePossibleMoves() {
    /*for (int i = 0; i < possible_moves.size(); i++) {
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
    }*/
    for (int i = 0; i < gameGridLayout->rowCount(); i++) {
        for (int j = 0; j < gameGridLayout->columnCount(); j++) {
            if (game->isBlackBox(i + 1, j + 1)) {
                QLayoutItem *item = gameGridLayout->itemAtPosition(i + 1,j + 1);
                if (item != 0) {
                    QWidget * widget = item->widget();
                    widget->setStyleSheet("background-color:rgb(0, 0, 0)");
                }
            }
        }
    }
}

void GameBoard::refresh() {
    //qDebug() << "gameboard refreshed";
    QList<QPair<uint, uint> >list;
    QString debug_str;
    QPointF point;
    QList<QPair<int,int> > pos_moves;
    clearBoard();
    if (possible_moves.count() != 0)
        hidePossibleMoves();


    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (game->board[i][j] == Game::MEN_POSSIBLE_MOVE) {
                pos_moves.append(QPair<int,int>(i,j));
            }
        }
    }
    if (pos_moves.count() != 0) {
        lightenPossibleMoves(pos_moves);
        QTimer::singleShot(2500, this, SLOT(toutExpired()));
    }
    if (game->getError().isEmpty()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (game->board[i][j] == Game::MEN_WHITE) {
                    debug_str += "white rock\t";
                    LightRock * light = new LightRock();
                    light_rocks.append(light);
                    point = this->convertCoords(j,i);
                    canvas->addItem(light);
                    light->setPos(67.5 + point.x(), 67.5 + point.y());

                }
                else if (game->board[i][j] == Game::MEN_BLACK) {
                    debug_str += "black rock\t";
                    DarkRock * dark = new DarkRock();
                    dark_rocks.append(dark);
                    point = this->convertCoords(j,i);
                    canvas->addItem(dark);
                    dark->setPos(67.5 + point.x(), 67.5 + point.y());
                }
                else if (game->board[i][j] == Game::MEN_WHITE_KING) {
                    debug_str += "white king\t";
                    LightRock * light = new LightRock();
                    light_rocks.append(light);
                    point = this->convertCoords(j,i);
                    canvas->addItem(light);
                    light->setPos(67.5 + point.x(), 67.5 + point.y());
                    light->becomeKing();

                }
                else if (game->board[i][j] == Game::MEN_BLACK_KING) {
                    debug_str += "black king\t";
                    DarkRock * dark = new DarkRock();
                    dark_rocks.append(dark);
                    point = this->convertCoords(j,i);
                    canvas->addItem(dark);
                    dark->setPos(67.5 + point.x(), 67.5 + point.y());
                    dark->becomeKing();
                }
                else if (game->board[i][j] == Game::MEN_POSSIBLE_MOVE) {
                    debug_str += "possible move\t";
                }
                else {
                    debug_str += "nothing\t";
                }
            }
            qDebug() << debug_str;
            debug_str = "";
        }
        lineedit_moves = game->getIcpSyntaxStr(false);
        MainWindow::getInstance()->setLineEditText(lineedit_moves);
    }
}

void GameBoard::clearBoard() {
    for (int i = 0; i < light_rocks.count(); i++) {
        delete light_rocks.at(i);
    }
    light_rocks.clear();
    for (int i = 0; i <dark_rocks.count(); i++) {
        delete dark_rocks.at(i);
    }
    dark_rocks.clear();
}

void GameBoard::showMoves(uint x, uint y) {
    game->showPossibleMoves(x - 1,y - 1);
}

void GameBoard::storeMove(uint srcx, uint srcy, uint destx, uint desty) {
    stored_src = QPair<uint,uint>(srcx, srcy);
    stored_dest = QPair<uint,uint>(destx, desty);
}

bool GameBoard::compareWithLastState() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ( stored_board_state[i][j] != game->board[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void GameBoard::sceneUpdate(uint srcx, uint srcy, uint destx, uint desty) {
    Game::err_t ret = game->move(srcx, srcy, destx, desty);
    if (ret != Game::ERR_OK) {
        MainWindow::getInstance()->setStatusMsg(game->getError());
        //MainWindow::getInstance()->setStatusMsg("error");
    }
}


void GameBoard::toutExpired() {
    game->hidePossibleMoves();
    hidePossibleMoves();
}
