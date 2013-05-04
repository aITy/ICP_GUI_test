#include "darkrock.h"
//#include "rock.h"
#include "ui_board.h"

#include <QDebug>

DarkRock::DarkRock(QWidget *parent)
        : QWidget(parent)
{
    this->resize(50, 50);
    this->setStyleSheet("background-image: url(:/dark_piece.png)");
}

DarkRock::~DarkRock() {

}
/*
void DarkRock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){}


void DarkRock::drawBackground(QPainter * painter, const QRectF &rect) {
    qDebug() << "CALLED";
    QRectF r;
    r.setRect(0,0, img.width(), img.height());
    painter->drawImage(r, img);
}
*/
QRectF DarkRock::getPosition() {
    return pos;
}

void DarkRock::setPosition(QRectF & p) {
    pos = p;
}
/*
QRectF DarkRock::boundingRect() const {
    return QRectF(0,0, img.width(), img.height());
}

void DarkRock::paintEvent(QPaintEvent * event) {
    Q_UNUSED(event);
    QPainter p(this);
    drawBackground(&p, QRectF(0,0, img.width(), img.height()));
}
*/
