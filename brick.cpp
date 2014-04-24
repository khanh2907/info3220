#include "brick.h"

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QRectF rec = boundingRect();
    QBrush brush("#84D9CF");

    if(m_colour != "#84D9CF"){
        brush.setColor(m_colour);
    }

    painter->setBrush(brush);
    painter->drawRect(rec);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}
