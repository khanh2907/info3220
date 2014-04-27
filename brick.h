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
#include "ball.h"

class Brick : public QObject, public QGraphicsItem{
public:

    Brick();

    Brick(int xCoordinate, int yCoordinate, int width, int height, int life, const char * colour);

    virtual ~Brick();

    virtual void advance(int phase);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QRectF boundingRect() const;

    QPoint * getPosition();
    int getWidth();
    int getHeight();
    int getLife();
    QColor getColour();
    int getXVelocity();

    virtual int decrementLife();

protected:
    QPoint *position;
    int m_width;
    int m_height;
    int m_life;
    QColor m_colour;
    int m_xVelocity;
};

#endif // BRICK_H
