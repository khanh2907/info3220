#include "ball.h"

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QRectF rec = boundingRect();
    QBrush brush("#84D9CF");
    if(colour != "#84D9CF"){
        brush.setColor(colour); //changes the colour of the ball depending on which side it hits
    }
    painter->setBrush(brush);
    painter->drawEllipse(rec);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

/*
 * Re-implemetation of QGraphics::advance, this function determines how to animate the next frame.
 * Below I check the window bounds with diameter rather than radius is because I set QRect boundingRect
 * to coordinates on the top left corner instead of the center.
 */
void Ball::advance(int phase){
    if (phase == 0){
      return;
    }

    int futureXPos = this->pos().x() + xVelocity;
    int futureYPos= this->pos().y() + yVelocity;
    int diameter = radius * 2;

    if(futureYPos <= 0){
        yVelocity *= -1;
        setPos(futureXPos, 0);
        colour = "#F0AFAF";
    }
    else if (futureXPos <= 0){
        xVelocity *= -1;
        setPos(0, futureYPos);
        colour = "#E5C1F5";
    }
    else if(futureYPos >= boxHeight - diameter){
        yVelocity *= -1;
        setPos(futureXPos, boxHeight - diameter);
        colour = "#FFFFAB";
    }
    else if (futureXPos >= boxWidth - diameter){
        xVelocity*= -1;
        setPos(boxWidth - diameter, futureYPos);
        colour = "#99BDF7";
    }
    else{
        setPos(futureXPos, futureYPos);
    }
}
