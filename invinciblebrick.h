#ifndef INVINCIBLEBRICK_H
#define INVINCIBLEBRICK_H
#include "brickdecorator.h"
#include <iostream>
class InvincibleBrick : public BrickDecorator
{
public:

    InvincibleBrick(Brick * other): BrickDecorator(other) {
        m_life = 999999;
    }
};

#endif // INVINCIBLEBRICK_H
