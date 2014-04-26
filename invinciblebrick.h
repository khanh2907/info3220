#ifndef INVINCIBLEBRICK_H
#define INVINCIBLEBRICK_H
#include "brickdecorator.h"
#include <iostream>
class InvincibleBrick : public BrickDecorator
{
public:

    InvincibleBrick(Brick * other): BrickDecorator(other) {}

    int decrementLife();
};

#endif // INVINCIBLEBRICK_H
