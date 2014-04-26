#ifndef BRICKDECORATOR_H
#define BRICKDECORATOR_H
#include "brick.h"
#include <iostream>

class BrickDecorator : public Brick
{
public:
    BrickDecorator() : Brick() {

    }

    BrickDecorator(Brick * innerBrick){
        position = innerBrick->getPosition();
        m_width = innerBrick->getWidth();
        m_height = innerBrick->getHeight();
        m_life = 999999;
        m_colour = innerBrick->getColour();
        setPos(mapToScene(*position));
    }

    ~BrickDecorator() {
        delete position;
    }

    virtual void decorate() = 0;

};

#endif // BRICKDECORATOR_H
