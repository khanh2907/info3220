#ifndef SLIDINGBRICK_H
#define SLIDINGBRICK_H
#include "brickdecorator.h"
#include <iostream>
class SlidingBrick : public BrickDecorator
{
public:
    SlidingBrick(Brick * other): BrickDecorator(other) {
        m_xVelocity = 2;
    }
};

#endif // SLIDINGBRICK_H
