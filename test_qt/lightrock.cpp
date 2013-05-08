#include "lightrock.h"
#include "ui_board.h"

#include <QDebug>

LightRock::LightRock()
{
    /*
    this->resize(50, 50);
    this->setStyleSheet("background-image: url(:/dark_piece.png)");
    */
    setFlag(ItemIsMovable);
    Pressed = false;
    king = false;
}

LightRock::~LightRock() {

}

QRectF LightRock::boundingRect() const {
    return QRectF(pos.x(), pos.y(), 50, 50);
}

void LightRock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){
    QRectF rect = boundingRect();
    QRectF src(0.0, 0.0, 50.0, 50.0);
    QImage img;
    if (!king)
        img = QImage(":/light_piece.png");
    else
        img = QImage(":/light_king.png");

    painter->drawImage(rect, img, src);
}

void LightRock::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void LightRock::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QPointF LightRock::getPosition() {
    return pos;
}

void LightRock::setPosition(QPointF p) {
    pos = p;
}

void LightRock::becomeKing() {
    king = true;
    this->update();
}

bool LightRock::isKing() {
    return king;
}
