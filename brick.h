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

class Brick : public QGraphicsItem{
public:

    Brick() {

    }

    Brick(int xCoordinate, int yCoordinate, int width, int height, int life, const char * colour) :
        position(new QPoint(xCoordinate, yCoordinate)),
        m_width(width),
        m_height(height),
        m_life(life),
        m_colour(QColor(colour))
    {
        setPos(mapToScene(*position));
    }

    virtual ~Brick(){
        delete position;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QRectF boundingRect() const { return QRectF(0, 0, m_width, m_height); }

    QPoint * getPosition() { return position;}
    int getWidth() { return m_width;}
    int getHeight() { return m_height;}
    int getLife() { return m_life;}
    QColor getColour() { return m_colour;}

    virtual int decrementLife() {
        m_life--;
        return m_life;
    }

protected:
    QPoint *position;
    int m_width;
    int m_height;
    int m_life;
    QColor m_colour;
};

#endif // BRICK_H
