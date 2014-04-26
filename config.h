#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <vector>

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

        int getxCoordinate() { return atoi(ball["xCoordinate"].c_str()); }
        int getyCoordinate() { return atoi(ball["yCoordinate"].c_str()); }
        int getRadius() { return atoi(ball["radius"].c_str()); }
        float getxVelocity() { return atof(ball["xVelocity"].c_str()); }
        float getyVelocity() { return atof(ball["yVelocity"].c_str()); }
        int getHeight() { return atoi(box["height"].c_str()); }
        int getWidth() { return atoi(box["width"].c_str()); }
        std::vector< std::map<std::string, std::string> > * getBricks() { return &bricks; }

    private:
        std::map<std::string, std::string> box;
        std::map<std::string, std::string> ball;
        std::vector< std::map<std::string, std::string> > bricks;
    };
}
#endif // CONFIG_H
