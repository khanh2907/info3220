#include "ball.h"
#include "brick.h"
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

    if (this == NULL) {
        return;
    }

    int currentXPos = this->pos().x();
    int currentYPos = this->pos().y();
    int futureXPos = currentXPos + xVelocity;
    int futureYPos= currentYPos + yVelocity;
    int diameter = radius * 2;

    if(futureYPos <= 0){
        yVelocity *= -1;
        futureYPos = 0;
        colour = "#F0AFAF";
    }
    else if (futureXPos <= 0){
        xVelocity *= -1;
        futureXPos = 0;
        colour = "#E5C1F5";
    }
    else if(futureYPos >= boxHeight - diameter){
        yVelocity *= -1;
        futureYPos = boxHeight - diameter;
        colour = "#FFFFAB";
    }
    else if (futureXPos >= boxWidth - diameter){
        xVelocity*= -1;
        futureXPos = boxWidth - diameter;
        colour = "#99BDF7";
    }
        QList<QGraphicsItem *> sceneItems = scene()->items();

        qreal futureBallTop = futureYPos;
        qreal futureBallBottom = futureYPos + diameter;
        qreal futureBallLeft = futureXPos;
        qreal futureBallRight = futureXPos + diameter;

        for( int i=0; i<sceneItems.count(); ++i ) {
            // make sure that it's not the ball

            if (sceneItems[i] == this)
                continue;

            Brick * thisBrick = dynamic_cast<Brick *>(sceneItems[i]);

            // do collision here because I hate qt libs
           qreal brickTop = thisBrick->pos().y();
           qreal brickBottom = thisBrick->pos().y() + thisBrick->getHeight();
           qreal brickLeft = thisBrick->pos().x();
           qreal brickRight = thisBrick->pos().x() + thisBrick->getWidth();

           //check if the future ball will be inside or touching the brick
           if (futureBallLeft <= brickRight && futureBallRight >= brickLeft && futureBallBottom >= brickTop && futureBallTop <= brickBottom) {
               // if it is inside then check which side the ball is going to hit
               // then send it back the other way
               if (currentXPos + diameter <= brickLeft) {
                   xVelocity *= -1;
                   futureXPos = brickLeft - diameter;
               }
               if (currentXPos >= brickRight) {
                   xVelocity *= -1;
                   futureXPos = brickRight;
               }
               if (currentYPos + diameter <= brickTop) {
                   yVelocity *= -1;
                   futureYPos = brickTop - diameter;
               }
               if (currentYPos >= brickBottom) {
                   yVelocity *= -1;
                   futureYPos = brickBottom;
               }

               // reduce brick life by one
               thisBrick->decrementLife();

           }
        }

        setPos(futureXPos, futureYPos);



}

