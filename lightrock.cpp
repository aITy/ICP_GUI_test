#include "lightrock.h"
//#include "rock.h"
#include "ui_board.h"

#include <QDebug>

LightRock::LightRock(QWidget *parent)
        : QWidget(parent)
{
    this->resize(50, 50);
    this->setStyleSheet("background-image: url(:/light_piece.png)");
}

LightRock::~LightRock() {

}

QRectF LightRock::getPosition() {
    return pos;
}

void LightRock::setPosition(QRectF & p) {
    pos = p;
}

