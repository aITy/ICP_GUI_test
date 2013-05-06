#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsWidget>

class GameBoard;

class Canvas : public QGraphicsScene
{
public:
    Canvas(GameBoard * parent);
private:
    GameBoard * board;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QString mouse_position;
    QPointF focused_item_pos;
    QString focused_item_type;

};

#endif // CANVAS_H
