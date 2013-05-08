#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsWidget>

class GameBoard;

class Canvas : public QGraphicsScene
{
    Q_OBJECT
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
    QString last_move;
signals:
     Q_SIGNALS:
    /** emitted whenever a board has changed (thus redraw is needed) */
    void sceneUpdated(uint, uint, uint, uint);
    void showPossibleMoves(uint, uint);

};

#endif // CANVAS_H
