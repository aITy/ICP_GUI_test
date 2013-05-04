#ifndef DARKROCK_H
#define DARKROCK_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

class DarkRock : public QWidget
{
    Q_OBJECT
public:
    DarkRock(QWidget * parent = 0);
    ~DarkRock();
    QRectF getPosition();
    void setPosition(QRectF & p);
private:
    QRectF pos;
protected:
    void paintEvent(QPaintEvent *pe) {
      QStyleOption o;
      o.initFrom(this);
      QPainter p(this);
      style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    };
};

#endif // DARKROCK_H
