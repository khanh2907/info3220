#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

namespace Config{
    //change this path depending on the location of your config file
    const std::string CONFIG_PATH ="/Users/khanh/INFO3220_Assignment/AssignmentTwoBaseOne/config.config";

    class Config{
    public:
        Config() : xCoordinate(0), yCoordinate(0), radius(10), xVelocity(1), yVelocity(1), height(400), width(400){
            readFile();
        }

        void readFile();
        void validate();
        std::string removeSpace(std::string);

        int getxCoordinate() { return xCoordinate; }
        int getyCoordinate() { return yCoordinate; }
        int getRadius() { return radius; }
        float getxVelocity() { return xVelocity; }
        float getyVelocity() { return yVelocity; }
        int getHeight() { return height; }
        int getWidth() { return width; }

    private:
        int xCoordinate;
        int yCoordinate;
        int radius;
        float xVelocity;
        float yVelocity;
        int height;
        int width;
    };
}
#endif // CONFIG_H
