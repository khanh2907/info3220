#include "itemfactory.h"

QGraphicsItem* ItemFactory::make(std::string item, Config::Config *config){

    if(item == "ball"){
        Ball *ball = new Ball(config->getxCoordinate(), config->getyCoordinate(), config->getRadius(),
                          config->getxVelocity(), config->getyVelocity(), "#84D9CF", config);
        return ball;
    }

    return NULL;
}
