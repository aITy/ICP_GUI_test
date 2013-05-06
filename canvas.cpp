#include "canvas.h"
#include "darkrock.h"
#include "lightrock.h"
#include "gameboard.h"
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

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    /*QString str = QString("%1, %2").arg(event->scenePos().x()).arg(event->scenePos().y());
    mouse_position = str;
    qDebug() << mouse_position;*/
    
    qreal pos_x = event->scenePos().x();
    qreal pos_y = event->scenePos().y();
    DarkRock *dark;
    LightRock *light;
    QGraphicsItem *can_jump;
    QGraphicsItem * item = this->itemAt(pos_x, pos_y);
   
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
            }else {
                if (last_move == "DarkRock") {
                    focused_item_type = "LightRock";
                    focused_item_pos = pos;
                }
            }

            QList <QPair<int, int> > str;
            str.append(QPair<int,int>(0,0));
            str.append(QPair<int,int>(0,4));
            str.append(QPair<int,int>(7,7));
            QList<QRectF> test = board->convertCoords(str);
            board->lightenPossibleMoves(str);

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
            if (focused_item_type != "DarkRock" && last_move == "DarkRock") {
                // jump left
                if (pos_x >= focused_item_pos.x() - 140.0 && pos_x <= focused_item_pos.x() - 70.0
                    && pos_y >= focused_item_pos.y() - 140.0 && pos_y <= focused_item_pos.y() - 70.0) {

                    // check boundaries
                    if (focused_item_pos.x() - 140.0 >= 65.0 && focused_item_pos.y() - 140.0 >= 70.0) {
                        //check presence od draught between areas
                        can_jump = this->itemAt(focused_item_pos.x() - 70.0, focused_item_pos.y() - 70.0);
                        if (can_jump != 0) {
                            if ((dark = dynamic_cast<DarkRock*>(can_jump))) {
                                // black rock in here
                                board->removeRock(dark->getPosition());
                                this->removeItem(can_jump);

                                itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(-140.0, -140.0);
                                last_move = "LightRock";
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
                        can_jump = this->itemAt(focused_item_pos.x() + 70.0, focused_item_pos.y() - 70.0);
                        if (can_jump != 0) {
                            if ((dark = dynamic_cast<DarkRock*>(can_jump))) {
                                // black rock in here
                                board->removeRock(dark->getPosition());
                                this->removeItem(can_jump);

                                itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(140.0, -140.0);
                                last_move = "LightRock";
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
                        itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(-70.0, -70.0);
                        last_move = "LightRock";
                    }
                }
                if (pos_x >= focused_item_pos.x() + 70.0 && pos_x <= focused_item_pos.x() + 140.0
                    && pos_y >= focused_item_pos.y() - 70.0 && pos_y <= focused_item_pos.y()) {
                    // move right
                    // check boundaries
                    if (focused_item_pos.x() + 70.0 <= 65.0 + this->sceneRect().width() && focused_item_pos.y() - 70.0 >= 70.0) {
                        // valid move to right
                        this->itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(70.0, -70.0);
                        last_move = "LightRock";
                    }
                }
            }
            else {
                if (last_move == "LightRock") {
                    // jump left
                    if (pos_x >= focused_item_pos.x() - 140.0 && pos_x <= focused_item_pos.x() - 70.0
                        && pos_y >= focused_item_pos.y() + 140.0 && pos_y <= focused_item_pos.y() + 210.0) {

                        // check boundaries
                        if (focused_item_pos.x() - 140.0 >= 65.0 && focused_item_pos.y() + 140.0 <= 70.0 + this->sceneRect().height()) {
                            //check presence od draught between areas
                            can_jump = this->itemAt(focused_item_pos.x() - 70.0, focused_item_pos.y() + 70.0);
                            if (can_jump != 0) {
                                if ((light = dynamic_cast<LightRock*>(can_jump))) {
                                    // black rock in here
                                    board->removeRock(light->getPosition());
                                    this->removeItem(can_jump);

                                    itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(-140.0, 140.0);
                                    last_move = "DarkRock";
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
                            can_jump = this->itemAt(focused_item_pos.x() + 70.0, focused_item_pos.y() + 70.0);
                            if (can_jump != 0) {
                                if ((light = dynamic_cast<LightRock*>(can_jump))) {
                                    // black rock in here
                                    board->removeRock(light->getPosition());
                                    this->removeItem(can_jump);

                                    itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(140.0, 140.0);
                                    last_move = "DarkRock";
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
                            itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(-70.0, 70.0);
                            last_move = "DarkRock";
                        }
                    }
                    if (pos_x >= focused_item_pos.x() + 70.0 && pos_x <= focused_item_pos.x() + 140.0
                        && pos_y >= focused_item_pos.y() + 70.0 && pos_y <= focused_item_pos.y() + 140.0) {
                        // move right
                        // check boundaries
                        if (focused_item_pos.x() + 70.0 <= 65.0 + this->sceneRect().width() && focused_item_pos.y() + 70.0 <= 70.0 + this->sceneRect().height()) {
                            // valid move to right
                            this->itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(70.0, 70.0);
                            last_move = "DarkRock";
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


