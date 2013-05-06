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
    QImage img(":/dark_piece.png");

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

void DarkRock::setPosition(QPointF & p) {
    pos = p;
}

