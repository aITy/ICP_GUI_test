#ifndef LIGHTROCK_H
#define LIGHTROCK_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

class LightRock : public QWidget
{
    Q_OBJECT
public:
    LightRock(QWidget * parent = 0);
    ~LightRock();
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

#endif // LIGHTROCK_H
