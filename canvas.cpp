#include "canvas.h"
#include "darkrock.h"
#include "gameboard.h"
#include <QDebug>

Canvas::Canvas(GameBoard *parent)
    :board(parent)
{
    focused_item_pos = QPointF(0.0, 0.0);
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    this->update();
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->update();
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QString str = QString("%1, %2").arg(event->scenePos().x()).arg(event->scenePos().y());
    mouse_position = str;
    //qDebug() << mouse_position;
    
    qreal pos_x = event->scenePos().x();
    qreal pos_y = event->scenePos().y();
   
    if (this->itemAt(pos_x, pos_y) != 0) {
        // area is occupied by rock
        QPointF pos = this->itemAt(pos_x, pos_y)->pos();
        focused_item_pos = pos;
        QGraphicsItem * item = this->itemAt(pos_x, pos_y);
        DarkRock *rock;
        if ((rock = dynamic_cast<DarkRock*>(item))) {
            focused_item_type = "DarkRock";
        }else {
            focused_item_type = "LightRock";
        }
        QList <QPair<QString, int> > str;
        str.append(QPair<QString,int>("a",0));
        board->lightenPossibleMoves(str);
    }
    else {
        if (focused_item_pos != QPointF(0.0,0.0)) {
            // some item is selected
            if (focused_item_type != "DarkRock") {
                // ordinary light rock move
                if (pos_x >= focused_item_pos.x() - 70.0 && pos_x <= focused_item_pos.x()
                    && pos_y >= focused_item_pos.y() - 70.0 && pos_y <= focused_item_pos.y()) {
                    // move left
                    // check boundaries
                    if (focused_item_pos.x() - 70.0 >= 65.0 && focused_item_pos.y() - 70.0 >= 70.0) {
                        // valid move to left
                        itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(-70.0, -70.0);
                    }
                }
                if (pos_x >= focused_item_pos.x() + 70.0 && pos_x <= focused_item_pos.x() + 140.0
                    && pos_y >= focused_item_pos.y() - 70.0 && pos_y <= focused_item_pos.y()) {
                    // move right
                    // check boundaries
                    if (focused_item_pos.x() + 70.0 <= 65.0 + this->sceneRect().width() && focused_item_pos.y() - 70.0 >= 70.0) {
                        // valid move to right
                        this->itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(70.0, -70.0);
                    }
                }
            }
            else {
                // ordinary dark rock move
                if (pos_x >= focused_item_pos.x() - 70.0 && pos_x <= focused_item_pos.x()
                    && pos_y >= focused_item_pos.y() + 70.0 && pos_y <= focused_item_pos.y() + 140.0) {
                    // move left
                    // check boundaries
                    if (focused_item_pos.x() - 70.0 >= 65.0 && focused_item_pos.y() + 70.0 <= 70.0 + this->sceneRect().height()) {
                        // valid move to left
                        itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(-70.0, 70.0);
                    }
                }
                if (pos_x >= focused_item_pos.x() + 70.0 && pos_x <= focused_item_pos.x() + 140.0
                    && pos_y >= focused_item_pos.y() + 70.0 && pos_y <= focused_item_pos.y() + 140.0) {
                    // move right
                    // check boundaries
                    if (focused_item_pos.x() + 70.0 <= 65.0 + this->sceneRect().width() && focused_item_pos.y() + 70.0 <= 70.0 + this->sceneRect().height()) {
                        // valid move to right
                        this->itemAt(focused_item_pos.x(), focused_item_pos.y())->moveBy(70.0, 70.0);
                    }
                }
            }
            
            // focus out
            focused_item_pos = QPointF(0.0, 0.0);

        }

    }
    
    
    this->update();
}
