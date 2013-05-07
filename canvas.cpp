#include "canvas.h"
#include "darkrock.h"
#include "lightrock.h"
#include "gameboard.h"
#include "mainwindow.h"
#include <QDebug>

Canvas::Canvas(GameBoard *parent)
    :board(parent)
{
    focused_item_pos = QPointF(0.0, 0.0);
    last_move = "DarkRock";
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    this->update();
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->update();
}

// TODO KINGS MOVE + JUMPS + MUST JUMP RULE
void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    /*QString str = QString("%1, %2").arg(event->scenePos().x()).arg(event->scenePos().y());
    mouse_position = str;
    qDebug() << mouse_position;*/
    
    qreal pos_x = event->scenePos().x();
    qreal pos_y = event->scenePos().y();
    DarkRock *dark;
    LightRock *light;
    QGraphicsItem *can_jump;
    QGraphicsItem *it;
    QGraphicsItem *item = this->itemAt(pos_x, pos_y);
    QList<QPair<QString, int> > ret;
    QList<QPointF> moves;
   
    if (item != 0) {
        // area is occupied by rock
        //qDebug() << event->scenePos();
        QPointF pos = item->pos();
        if (focused_item_pos == QPointF(0.0, 0.0)) {

            if ((dark = dynamic_cast<DarkRock*>(item))) {
                if (last_move == "LightRock") {
                    focused_item_type = "DarkRock";
                    focused_item_pos = pos;
                }
                else {
                    MainWindow::getInstance()->setStatusMsg("White player is on move!");
                }
            }else {
                if (last_move == "DarkRock") {
                    focused_item_type = "LightRock";
                    focused_item_pos = pos;
                }
                else {
                    MainWindow::getInstance()->setStatusMsg("Black player is on move!");
                }
            }
/*
            QList <QPair<int, int> > str;
            str.append(QPair<int,int>(0,0));
            str.append(QPair<int,int>(0,4));
            str.append(QPair<int,int>(7,7));
            QList<QRectF> test = board->convertCoords(str);
            board->lightenPossibleMoves(str);
*/
        }
        else {
            if (focused_item_type == "DarkRock") {
                if ((dark = dynamic_cast<DarkRock*>(item))) {
                    focused_item_pos = pos;
                    focused_item_type = "DarkRock";
                }

            }
            else {
                if ((light = dynamic_cast<LightRock*>(item))) {
                    focused_item_pos = pos;
                    focused_item_type = "LightRock";
                }
            }
        }
    }
    else {
        if (focused_item_pos != QPointF(0.0,0.0)) {
            //board->hidePossibleMoves();
            // some item is selected
            if (focused_item_type != "DarkRock") {
                if (last_move == "DarkRock") {
                    light = dynamic_cast<LightRock*>(itemAt(focused_item_pos.x(), focused_item_pos.y()));
                    if (light->isKing()) {
                        // TODO KING MOVES AND JUMPS
                        // move or jump on right bottom diagonal
                        int x = focused_item_pos.x() + 70 + 7.5;
                        int y = focused_item_pos.y() + 70 + 7.5;
                        while(itemAt(x,y) == 0 && x <= 67.5 + this->width() && y <= 67.5 + this->height()) {
                            x += 70; y += 70;
                        }
                        if(itemAt(x,y) != 0) {
                            // might jump
                            if (pos_x >= x + 70 && pos_x <= x + 140 && pos_y >= y + 70 && pos_y <= y + 140) {
                                can_jump = itemAt(x,y);
                                if ((dark = dynamic_cast<DarkRock*>(can_jump))) {
                                    // jump
                                    moves.append(focused_item_pos);
                                    moves.append(QPointF(x + 70, y + 70));
                                    ret = board->convertCoords(moves, QString("output"));
                                    moves.clear();
                                    MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("JUMP"));

                                    board->removeRock(itemAt(x, y)->pos());
                                    this->removeItem(can_jump);

                                    itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(x - 7.5 - focused_item_pos.x() + 70, y - 7.5 - focused_item_pos.y() + 70);
                                    last_move = "LightRock";
                                }

                            }
                        }
                    }
                    else {
                        // jump left
                        if (pos_x >= focused_item_pos.x() - 140.0 && pos_x <= focused_item_pos.x() - 70.0
                            && pos_y >= focused_item_pos.y() - 140.0 && pos_y <= focused_item_pos.y() - 70.0) {

                            // check boundaries
                            if (focused_item_pos.x() - 140.0 >= 65.0 && focused_item_pos.y() - 140.0 >= 70.0) {
                                //check presence od draught between areas
                                can_jump = itemAt(focused_item_pos.x() - 70.0, focused_item_pos.y() - 70.0);
                                if (can_jump != 0) {
                                    if ((dark = dynamic_cast<DarkRock*>(can_jump))) {

                                        moves.append(focused_item_pos);
                                        moves.append(QPointF(focused_item_pos.x() - 140, focused_item_pos.y() - 140));
                                        ret = board->convertCoords(moves, QString("output"));
                                        moves.clear();
                                        MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("JUMP"));
                                        // black rock in here
                                        board->removeRock(itemAt(focused_item_pos.x() - 70.0, focused_item_pos.y() - 70.0)->pos());
                                        this->removeItem(can_jump);

                                        it = itemAt(focused_item_pos.x(), focused_item_pos.y());
                                        it->moveBy(-140.0, -140.0);
                                        last_move = "LightRock";
                                        if (pos_y <= 67.5 + 70 && pos_y >= 67.5) {
                                            light = dynamic_cast<LightRock*>(it);
                                            light->becomeKing();
                                        }


                                    }
                                }
                            }
                        }
                        // jump right
                        if (pos_x >= focused_item_pos.x() + 140.0 && pos_x <= focused_item_pos.x() + 210.0
                            && pos_y >= focused_item_pos.y() - 140.0 && pos_y <= focused_item_pos.y() - 70.0) {

                            // check boundaries
                            if (focused_item_pos.x() + 140.0 <= 65.0 + this->sceneRect().width() && focused_item_pos.y() - 140.0 >= 70.0) {
                                //check presence od draught between areas
                                can_jump = itemAt(focused_item_pos.x() + 70.0, focused_item_pos.y() - 70.0);
                                if (can_jump != 0) {
                                    if ((dark = dynamic_cast<DarkRock*>(can_jump))) {
                                        // black rock in here
                                        moves.append(focused_item_pos);
                                        moves.append(QPointF(focused_item_pos.x() + 140, focused_item_pos.y() - 140));
                                        ret = board->convertCoords(moves, QString("output"));
                                        moves.clear();
                                        MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("JUMP"));

                                        board->removeRock(itemAt(focused_item_pos.x() + 70.0, focused_item_pos.y() - 70.0)->pos());
                                        this->removeItem(can_jump);

                                        it = itemAt(focused_item_pos.x(), focused_item_pos.y());
                                        it->moveBy(140.0, -140.0);
                                        last_move = "LightRock";
                                        if (pos_y <= 67.5 + 70 && pos_y >= 67.5) {
                                            light = dynamic_cast<LightRock*>(it);
                                            light->becomeKing();
                                        }
                                    }
                                }
                            }
                        }

                        // ordinary light rock move
                        if (pos_x >= focused_item_pos.x() - 70.0 && pos_x <= focused_item_pos.x()
                            && pos_y >= focused_item_pos.y() - 70.0 && pos_y <= focused_item_pos.y()) {
                            // move left
                            // check boundaries
                            if (focused_item_pos.x() - 70.0 >= 65.0 && focused_item_pos.y() - 70.0 >= 70.0) {
                                // valid move to left
                                moves.append(focused_item_pos);
                                moves.append(QPointF(focused_item_pos.x() - 70, focused_item_pos.y() - 70));
                                ret = board->convertCoords(moves, QString("output"));
                                moves.clear();
                                MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("MOVE"));
                                it = itemAt(focused_item_pos.x(), focused_item_pos.y());
                                it->moveBy(-70.0, -70.0);
                                if (pos_y <= 67.5 + 70 && pos_y >= 67.5) {
                                    light = dynamic_cast<LightRock*>(it);
                                    light->becomeKing();
                                }
                                last_move = "LightRock";
                            }
                        }
                        if (pos_x >= focused_item_pos.x() + 70.0 && pos_x <= focused_item_pos.x() + 140.0
                            && pos_y >= focused_item_pos.y() - 70.0 && pos_y <= focused_item_pos.y()) {
                            // move right
                            // check boundaries
                            if (focused_item_pos.x() + 70.0 <= 65.0 + this->sceneRect().width() && focused_item_pos.y() - 70.0 >= 70.0) {
                                // valid move to right
                                moves.append(focused_item_pos);
                                moves.append(QPointF(focused_item_pos.x() + 70, focused_item_pos.y() - 70));
                                ret = board->convertCoords(moves, QString("output"));
                                moves.clear();
                                MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("MOVE"));
                                it = this->itemAt(focused_item_pos.x(), focused_item_pos.y());
                                it->moveBy(70.0, -70.0);
                                if (pos_y <= 67.5 + 70 && pos_y >= 67.5) {
                                    light = dynamic_cast<LightRock*>(it);
                                    light->becomeKing();
                                }
                                last_move = "LightRock";
                            }
                        }
                    }
                }
            }
            else {
                if (last_move == "LightRock") {
                    dark = dynamic_cast<DarkRock*>(itemAt(focused_item_pos.x(), focused_item_pos.y()));
                    if (dark->isKing()) {
                        // TODO KINGS MOVES + JUMPS
                    }
                    else {
                        // jump left
                        if (pos_x >= focused_item_pos.x() - 140.0 && pos_x <= focused_item_pos.x() - 70.0
                            && pos_y >= focused_item_pos.y() + 140.0 && pos_y <= focused_item_pos.y() + 210.0) {

                            // check boundaries
                            if (focused_item_pos.x() - 140.0 >= 65.0 && focused_item_pos.y() + 140.0 <= 70.0 + this->sceneRect().height()) {
                                //check presence od draught between areas
                                can_jump = itemAt(focused_item_pos.x() - 70.0, focused_item_pos.y() + 70.0);
                                if (can_jump != 0) {
                                    if ((light = dynamic_cast<LightRock*>(can_jump))) {
                                        // black rock in here
                                        moves.append(focused_item_pos);
                                        moves.append(QPointF(focused_item_pos.x() - 140, focused_item_pos.y() + 140));
                                        ret = board->convertCoords(moves, QString("output"));
                                        moves.clear();
                                        MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("JUMP"));

                                        board->removeRock(itemAt(focused_item_pos.x() - 70.0, focused_item_pos.y() + 70.0)->pos());
                                        this->removeItem(can_jump);

                                        it = itemAt(focused_item_pos.x(), focused_item_pos.y());
                                        it->moveBy(-140.0, 140.0);
                                        last_move = "DarkRock";
                                        if (pos_y <= 70 + this->height() && pos_y >= this->height()) {
                                            dark = dynamic_cast<DarkRock*>(it);
                                            dark->becomeKing();
                                        }
                                    }
                                }
                            }
                        }
                        // jump right
                        if (pos_x >= focused_item_pos.x() + 140.0 && pos_x <= focused_item_pos.x() + 210.0
                            && pos_y >= focused_item_pos.y() + 140.0 && pos_y <= focused_item_pos.y() + 210.0) {

                            // check boundaries
                            if (focused_item_pos.x() + 140.0 <= 65.0 + this->sceneRect().width() && focused_item_pos.y() + 140.0 <= 70.0 + this->sceneRect().height()) {
                                //check presence od draught between areas
                                can_jump = itemAt(focused_item_pos.x() + 70.0, focused_item_pos.y() + 70.0);
                                if (can_jump != 0) {
                                    if ((light = dynamic_cast<LightRock*>(can_jump))) {
                                        // black rock in here
                                        moves.append(focused_item_pos);
                                        moves.append(QPointF(focused_item_pos.x() + 140, focused_item_pos.y() + 140));
                                        ret = board->convertCoords(moves, QString("output"));
                                        moves.clear();
                                        MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("JUMP"));

                                        board->removeRock(itemAt(focused_item_pos.x() + 70.0, focused_item_pos.y() + 70.0)->pos());
                                        this->removeItem(can_jump);

                                        it = itemAt(focused_item_pos.x(), focused_item_pos.y());
                                        it->moveBy(140.0, 140.0);
                                        last_move = "DarkRock";
                                        if (pos_y <= 70 + this->height() && pos_y >= this->height()) {
                                            dark = dynamic_cast<DarkRock*>(it);
                                            dark->becomeKing();
                                        }
                                    }
                                }
                            }
                        }
                        // ordinary dark rock move
                        if (pos_x >= focused_item_pos.x() - 70.0 && pos_x <= focused_item_pos.x()
                            && pos_y >= focused_item_pos.y() + 70.0 && pos_y <= focused_item_pos.y() + 140.0) {
                            // move left
                            // check boundaries
                            if (focused_item_pos.x() - 70.0 >= 65.0 && focused_item_pos.y() + 70.0 <= 70.0 + this->sceneRect().height()) {
                                // valid move to left
                                moves.append(focused_item_pos);
                                moves.append(QPointF(focused_item_pos.x() - 70, focused_item_pos.y() + 70));
                                ret = board->convertCoords(moves, QString("output"));
                                moves.clear();
                                MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("MOVE"));
                                it = itemAt(focused_item_pos.x(), focused_item_pos.y());
                                it->moveBy(-70.0, 70.0);
                                if (pos_y <= 70 + this->height() && pos_y >= this->height()) {
                                    dark = dynamic_cast<DarkRock*>(it);
                                    dark->becomeKing();
                                }
                                last_move = "DarkRock";
                            }
                        }
                        if (pos_x >= focused_item_pos.x() + 70.0 && pos_x <= focused_item_pos.x() + 140.0
                            && pos_y >= focused_item_pos.y() + 70.0 && pos_y <= focused_item_pos.y() + 140.0) {
                            // move right
                            // check boundaries
                            if (focused_item_pos.x() + 70.0 <= 65.0 + this->sceneRect().width() && focused_item_pos.y() + 70.0 <= 70.0 + this->sceneRect().height()) {
                                // valid move to right
                                moves.append(focused_item_pos);
                                moves.append(QPointF(focused_item_pos.x() + 70, focused_item_pos.y() + 70));
                                ret = board->convertCoords(moves, QString("output"));
                                moves.clear();
                                MainWindow::getInstance()->addMove(ret.at(0), ret.at(1), QString("MOVE"));
                                it = itemAt(focused_item_pos.x(), focused_item_pos.y());
                                it->moveBy(70.0, 70.0);
                                 if (pos_y <= 70 + this->height() && pos_y >= this->height()) {
                                    dark = dynamic_cast<DarkRock*>(it);
                                    dark->becomeKing();
                                }
                                last_move = "DarkRock";
                            }
                        }
                    }
                }
            }
            
            // focus out
            focused_item_pos = QPointF(0.0, 0.0);
        }

    }
    
    
    this->update();
}


