#ifndef INVINCIBLEBRICK_H
#define INVINCIBLEBRICK_H
#include "brickdecorator.h"
#include <iostream>
class InvincibleBrick : public BrickDecorator
{
public:

    InvincibleBrick(Brick * innerBrick): BrickDecorator(innerBrick) {}

    void decorate() {
        std::cout << "decorate" << std::endl;
    }
};

#endif // INVINCIBLEBRICK_H
