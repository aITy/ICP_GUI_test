#ifndef DARKROCK_H
#define DARKROCK_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QGraphicsItem>

class DarkRock : public QGraphicsItem
{
public:
    DarkRock();
    ~DarkRock();
    QRectF getPosition();
    void setPosition(QRectF & p);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget);
    bool Pressed;
private:
    QRectF pos;
protected:
    /*
    void paintEvent(QPaintEvent *pe) {
      QStyleOption o;
      o.initFrom(this);
      QPainter p(this);
      style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    };*/
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // DARKROCK_H
