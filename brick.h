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
    Brick(int xCoordinate, int yCoordinate, int width, int height, const char * colour) :
        position(new QPoint(xCoordinate, yCoordinate)),
        m_width(width),
        m_height(height),
        m_colour(QColor(colour))
    {
        setPos(mapToScene(*position));
    };

    virtual ~Brick(){
        delete position;
    }

//    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QRectF boundingRect() const { return QRectF(0, 0, m_width, m_height); }

private:
    QPoint *position;
    int m_width;
    int m_height;
    QColor m_colour;
};

#endif // BRICK_H
