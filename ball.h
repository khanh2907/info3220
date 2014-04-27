#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QPainter>
#include <QColor>
#include "config.h"

class Ball : public QGraphicsItem{
public:
    Ball(int xCoordinate, int yCoordinate, int radius, float xVelocity, float yVelocity, QColor colour,
         Config::Config * config) : position(new QPoint(xCoordinate, yCoordinate)), radius(radius),
         xVelocity(xVelocity), yVelocity(yVelocity), boxWidth(config->getWidth()),
         boxHeight(config->getHeight()), colour(colour){
         setPos(mapToScene(*position));
         setData(1, "Ball");
    }

    virtual ~Ball(){
        delete position;
    }

    /* The QGraphicsScene searches for the QGraphicsItem::advance and paint
     * in order for us to animate the ball
     */
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    /* Fames around the item (ball). This function returns QRectF(0, 0, radius*2, radius*2)
     * meaning the origin of the ball/item has moved from the center to the top
     * left corner of the frame
     */
    QRectF boundingRect() const { return QRectF(0, 0, radius*2, radius*2); }
    void playSound();

    QPoint * getPosition() { return position; }
    int getRadius() const { return radius; }
    float getxVelocity() { return xVelocity; }
    float getyVelocity() { return yVelocity; }
    int getBoxWidth() { return boxWidth; }
    int getBoxHeight() { return boxHeight; }

private:
    QPoint *position;
    int radius;
    float xVelocity;
    float yVelocity;
    int boxWidth;
    int boxHeight;
    QColor colour;
};

#endif // BALL_H
