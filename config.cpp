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

        std::string currentSet;
        std::string key, value;

        while (std::getline(file, buffer)){
            // ignore blank lines
            if (!buffer.length()) continue;

            int indexOfColon = buffer.find(':');

            if (buffer[0] == '[' && buffer[buffer.length()-1] == ']') {
                currentSet = buffer.substr(1, buffer.length()-2);
                transform(currentSet.begin(), currentSet.end(), currentSet.begin(), ::tolower);
            }

            else {

                key = removeSpace(buffer.substr(0, indexOfColon));
                value = removeSpace(buffer.substr(indexOfColon + 1));

                if (currentSet == "box") {
                    box[key] = value;
                }

                else if (currentSet == "ball") {
                    ball[key] = value;
                }

                else if (currentSet == "bricks") {
                    std::istringstream ss(value);
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
                        // todo: check for missing values, optional ones like color, malformed ones
                        if (valCount < 6){
                            thisBrick[brickKey] = brickVal;
                        }
                        valCount++;
                    }
                    bricks.push_back(thisBrick);
                }
            }
        }
        file.close();
    }
//    validate();
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

//void Config::Config::validate(){
//    if(width < 0  ||
//       height < 0 ||
//       radius < 0 ||
//       xCoordinate < 0 ||
//       yCoordinate < 0){
//        std::cout<<"Cannot have negative width, height, radius or xy coordinates"<<std::endl;
//        exit(0);
//    }

//    if(height < yCoordinate + 2*radius ||
//       width < xCoordinate + 2*radius){
//        std::cout<<"The ball doesn't fit within the box dimensons"<<std::endl;
//        exit(0);
//    }
//}
