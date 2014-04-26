#ifndef BRICKDECORATOR_H
#define BRICKDECORATOR_H
#include "brick.h"
#include <iostream>

class BrickDecorator : public Brick
{
public:
    BrickDecorator() : Brick() {

    }

    BrickDecorator(Brick * other){
        qreal xCoordinate = other->pos().x();
        qreal yCoordinate = other->pos().y();
        position = new QPoint(xCoordinate, yCoordinate);
        m_width = other->getWidth();
        m_height = other->getHeight();
        m_life = other->getLife();
        m_colour = other->getColour();
        setPos(mapToScene(*position));
        delete other;
    }

    virtual void decorate(){
        std::cout << "Decorate not implemented!" << std::endl;
    }
};

#endif // BRICKDECORATOR_H
