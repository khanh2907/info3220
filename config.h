#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <algorithm>

namespace Config{
    //change this path depending on the location of your config file
    const std::string CONFIG_PATH ="/Users/khanh/INFO3220_Assignment/AssignmentTwoBaseOne/config.config";

    class Config{
    public:
        Config(){
            readFile();
        }

        void readFile();
        void validate();
        std::string removeSpace(std::string);
        bool isInt(std::string s);

        int getxCoordinate() { return xCoordinate; }
        int getyCoordinate() { return yCoordinate; }
        int getRadius() { return radius; }
        float getxVelocity() { return xVelocity; }
        float getyVelocity() { return yVelocity; }
        int getHeight() { return height; }
        int getWidth() { return width; }
        std::vector< std::map<std::string, std::string> > * getBricks() { return &bricks; }

    private:
        int xCoordinate;
        int yCoordinate;
        int radius;
        float xVelocity;
        float yVelocity;
        int height;
        int width;
        std::vector< std::map<std::string, std::string> > bricks;
    };
}
#endif // CONFIG_H
