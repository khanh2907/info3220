#include "Config.h"

void Config::Config::readFile(){
    std::string buffer;
    std::string buffer2;
    std::ifstream file(CONFIG_PATH.c_str());
    if(file.fail()){
        std::cout<<"Missing configuration file"<<std::endl;
        exit(0);
    }
    if (file.is_open()){
        bool bricksInput = false;
        while (std::getline(file, buffer)){

            if (!buffer.length()) continue;

            std::stringstream line(buffer);
            //reading the number input from .config
            while(std::getline(line, buffer2, ':')){
                buffer2 = removeSpace(buffer2);
                buffer = removeSpace(buffer);
                if(buffer2 == "height"){
                    std::string str = buffer.substr(7,buffer.length());
                    height = atoi(str.c_str());
                }
                else if(buffer2 == "width"){
                    std::string str = buffer.substr(6,buffer.length());
                    width = atoi(str.c_str());
                }
                else if(buffer2 == "radius"){
                    std::string str = buffer.substr(7,buffer.length());
                    radius = atoi(str.c_str());
                }
                else if(buffer2 == "xCoordinate"){
                    std::string str = buffer.substr(12,buffer.length());
                    xCoordinate = atoi(str.c_str());
                }
                else if(buffer2 == "yCoordinate"){
                    std::string str = buffer.substr(12,buffer.length());
                    yCoordinate = atoi(str.c_str());
                }
                else if(buffer2 == "xVelocity"){
                    std::string str = buffer.substr(10,buffer.length());
                    xVelocity = atof(str.c_str());
                }
                else if(buffer2 == "yVelocity"){
                    std::string str = buffer.substr(10,buffer.length());
                    yVelocity = atof(str.c_str());
                }
            }

            if (bricksInput) {
                int indexOfColon = buffer.find(':');
                std::string brickName = removeSpace(buffer.substr(0, indexOfColon));
                std::string csv = removeSpace(buffer.substr(indexOfColon+1));

                std::istringstream ss(csv);
                std::string brickVal;
                std::map<std::string, std::string> thisBrick;

                int valCount = 0;

                while(std::getline(ss, brickVal, ',')) {
                    std::string brickKey;
                    if (0 == valCount) brickKey = "xCoordinate";
                    else if (1 == valCount) brickKey = "yCoordinate";
                    else if (2 == valCount) brickKey = "width";
                    else if (3 == valCount) brickKey = "height";
                    else if (4 == valCount) brickKey = "life";
                    else if (5 == valCount) brickKey = "colour";

                    // special bricks
                    if (valCount > 5) {
                        if (brickVal == "SLD" || brickVal == "INV" || brickVal == "TEL")
                            brickKey = brickVal;
                        else
                            continue;
                    }

                    thisBrick[brickKey] = brickVal;
                    valCount++;

                }
                bricks.push_back(thisBrick);
            }

            if (buffer == "[BRICKS]")
                bricksInput = true;

        }
        file.close();
    }
    validate();
}

std::string Config::Config::removeSpace(std::string s){
    std::string newStr;
    for(std::string::size_type i = 0; i<s.length(); i++){
        if(s.at(i) != ' '){
            newStr += s.at(i);
        }
    }
    return newStr;
}

void Config::Config::validate(){
    if(width < 0  ||
       height < 0 ||
       radius < 0 ||
       xCoordinate < 0 ||
       yCoordinate < 0){
        std::cout<<"Cannot have negative width, height, radius or xy coordinates"<<std::endl;
        exit(0);
    }

    if(height < yCoordinate + 2*radius ||
       width < xCoordinate + 2*radius){
        std::cout<<"The ball doesn't fit within the box dimensons"<<std::endl;
        exit(0);
    }
}
