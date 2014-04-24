#include "brick.h"

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QRectF rec = boundingRect();
    QBrush brush("#84D9CF");

    painter->setBrush(brush);
    painter->drawRect(rec);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}
