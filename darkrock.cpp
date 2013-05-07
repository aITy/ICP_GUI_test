#include "darkrock.h"
//#include "rock.h"
#include "ui_board.h"

#include <QDebug>

DarkRock::DarkRock()
{
    /*
    this->resize(50, 50);
    this->setStyleSheet("background-image: url(:/dark_piece.png)");
    */
    Pressed = false;
    king = false;
    setFlag(ItemIsMovable);
}

DarkRock::~DarkRock() {

}

QRectF DarkRock::boundingRect() const {
    return QRectF(pos.x(), pos.y(), 50, 50);
}

void DarkRock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){
    QRectF rect = boundingRect();
    QRectF src(0.0, 0.0, 50.0, 50.0);
    QImage img;
    if (!king)
        img = QImage(":/dark_piece.png");
    else
        img = QImage(":/dark_king.png");

    painter->drawImage(rect, img, src);
}

void DarkRock::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void DarkRock::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}


QPointF DarkRock::getPosition() {
    return pos;
}

void DarkRock::setPosition(QPointF p) {
    pos = p;
}

void DarkRock::becomeKing() {
    king = true;
    this->update();
}
