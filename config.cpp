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
        std::string currentSet = "";
        while (std::getline(file, buffer)){

            // ignore blank lines
            if (!buffer.length()) continue;

            // ignore # comments
            if (buffer[0] == '#') continue;

            int indexOfColon = buffer.find(':');

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

            // make sure invalid lines are handled
            if ((currentSet == "bricks" || currentSet == "ball" || currentSet == "box") && (buffer[0] != '[' && buffer[buffer.length()-1] != ']')){
                if (indexOfColon == -1) {
                    std::cout << "Invalid line detected in config file: " << buffer << std::endl;
                    exit(0);
                }
            }

            // get brick info here
            if (currentSet == "bricks") {

                std::string csv = removeSpace(buffer.substr(indexOfColon+1));
                std::string brickName = removeSpace(buffer.substr(0, indexOfColon));
                std::istringstream ss(csv);
                std::string brickVal;
                std::map<std::string, std::string> thisBrick;

                thisBrick["name"] = brickName;

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
                        if (brickVal == "SLD" || brickVal == "INV")
                            brickKey = brickVal;
                        else {
                            std::cout << brickVal <<" is not a valid brick modifier." << std::endl;
                            exit(1);
                        }
                    }

                    thisBrick[brickKey] = brickVal;
                    valCount++;

                }
                bricks.push_back(thisBrick);
            }

            if (buffer[0] == '[' && buffer[buffer.length()-1] == ']') {
                currentSet = buffer.substr(1, buffer.length()-2);
                transform(currentSet.begin(), currentSet.end(), currentSet.begin(), ::tolower);
            }

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

bool Config::Config::isInt(std::string s)
{

   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;

}

void Config::Config::validate(){
    if(width < 0  ||
       height < 0 ||
       radius < 0 ||
       xCoordinate < 0 ||
       yCoordinate < 0){
        std::cout<<"Cannot have negative width, height, radius or xy coordinates"<<std::endl;
        exit(1);
    }

    if(height < yCoordinate + 2*radius ||
       width < xCoordinate + 2*radius){
        std::cout<<"The ball doesn't fit within the box dimensons"<<std::endl;
        exit(1);
    }

    // params to check type and validity
    std::map<std::string, std::string> paramsToCheck;
    paramsToCheck["xCoordinate"] = "int";
    paramsToCheck["yCoordinate"] = "int";
    paramsToCheck["width"] = "int";
    paramsToCheck["height"] = "int";
    paramsToCheck["life"] = "int";
    paramsToCheck["colour"] = "colour";

    for(auto iter = bricks.begin(); iter != bricks.end(); iter++) {
        auto thisBrick = *(iter);
        for (auto paramsIt = paramsToCheck.begin(); paramsIt != paramsToCheck.end(); paramsIt++) {
            std::string param = paramsIt->first;
            std::string type = paramsIt->second;

            // check the ints in the brick
            if (type == "int") {
                if (!isInt(thisBrick[param])) {
                    std::cout << thisBrick["name"]<< " " << param << " must be an int." << std::endl;
                    exit(1);
                }
                else {
                    int thisInt = atoi(thisBrick[param].c_str());

                    if (thisInt < 0) {
                        std::cout << thisBrick["name"]<< " "<< param << " must be positive." << std::endl;
                        exit(1);
                    }


                }
            }

            // check the colour
            if (type == "colour") {
                std::string val = thisBrick[param];
                if (val[0] != '#' || (val.length() != 4 && val.length() != 7)) {
                    std::cout << thisBrick["name"]<< " "<< param << " must start with a # followed by 3 or 6 digit hex value representing a colour." << std::endl;
                    exit(1);
                }
            }

        }

        // make sure life is > 0
        if (atoi(thisBrick["life"].c_str()) <= 0) {
            std::cout << thisBrick["name"]<< " life must be greater than 0." << std::endl;
            exit(1);
        }
    }
}
