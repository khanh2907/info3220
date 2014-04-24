#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <iostream>
#include "ball.h"
#include "config.h"

class ItemFactory{
public:
    static QGraphicsItem* make(std::string item, Config::Config *config);
};

#endif // ITEMFACTORY_H
