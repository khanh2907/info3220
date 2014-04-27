#ifndef BRICKDECORATOR_H
#define BRICKDECORATOR_H
#include "brick.h"
#include <iostream>

class BrickDecorator : public Brick
{
public:
    BrickDecorator() : Brick() {}

    BrickDecorator(Brick * other);

    virtual void advance(int phase);
};

#endif // BRICKDECORATOR_H
