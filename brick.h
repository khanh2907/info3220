#ifndef BRICK_H
#define BRICK_H

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QPainter>
#include <QColor>
#include "config.h"

class Brick : public QGraphicsItem{
public:
    Brick(int xCoordinate, int yCoordinate, int width, int height) : position(new QPoint(xCoordinate, yCoordinate)), m_width(width), m_height(height)
    {
        setPos(mapToScene(*position));
    };

    virtual ~Brick(){
        delete position;
    }

//    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QRectF boundingRect() const { return QRectF(position->x(), position->y(), m_width, m_height); }

private:
    QPoint *position;
    int m_width;
    int m_height;
};

#endif // BRICK_H
