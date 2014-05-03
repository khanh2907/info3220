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
                else if(buffer2 == "brickGen"){
                    std::string str = buffer.substr(9,buffer.length());
                    brickGen = (str == "on");
                }
            }

            // make sure invalid lines are handled
            if ((currentSet == "bricks" || currentSet == "ball" || currentSet == "box") && (buffer[0] != '[' && buffer[buffer.length()-1] != ']')){
                if (indexOfColon == -1) {
                    std::cout << "Invalid line detected in config file: " << buffer << std::endl;
                    exit(0);
                }
            }

            // determine the current set
            if (buffer[0] == '[' && buffer[buffer.length()-1] == ']') {
                currentSet = buffer.substr(1, buffer.length()-2);
                transform(currentSet.begin(), currentSet.end(), currentSet.begin(), ::tolower);
                continue;
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

        }
        file.close();
    }
    if (brickGen) {
        generateBricks();
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
                    std::cout << thisBrick[param] << std::endl;
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
                if (val[0] != '#') {
                    std::cout << thisBrick["name"]<< " "<< param << " must start with a #" << std::endl;
                    std::cout << thisBrick[param] << std::endl;
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

// Running this function will clear any given bricks from the config file.
// It will proceed to create a random number of bricks with random attributes.
void Config::Config::generateBricks() {

    bricks.clear();

    srand(time(NULL));
    int minHeight = 5;
    int maxHeight = 20;
    int minWidth = 40;
    int maxWidth = 70;
    int maxLife = 15;

    int numOfBricks = rand()%100 + 10;

    for (int i=0; i< numOfBricks; i++) {
        std::map<std::string, std::string> thisBrick;
        int rngHeight = rand()%maxHeight + minHeight;
        int rngWidth = rand()%maxWidth + minWidth;

        int rngX = rand()%width;
        int rngY = rand()%height;

        int rngLife = rand()%maxLife + 1;

        // generate a random hex value for colour
        int x = rand() & 0xff;
        x |= (rand() & 0xff) << 8;
        x |= (rand() & 0xff) << 16;
        std::stringstream stream;
        stream << "#" << std::hex << x;
        std::string rngColour( stream.str() );

        // name of brick
        stream.str(std::string());
        stream << "brick" << i;
        std::string brickName = stream.str();

        // small chance of special being special
        int specialChance = rand()%20;

        if (specialChance >= 16) {
            int invChance = rand()%2;
            int sldChance = rand()%2;

            if (invChance) {
                thisBrick["INV"] = "INV";
            }

            if (sldChance) {
                thisBrick["SLD"] = "SLD";
            }
        }

        thisBrick["xCoordinate"] = intToString(rngX);
        thisBrick["yCoordinate"] = intToString(rngY);
        thisBrick["width"] = intToString(rngWidth);
        thisBrick["height"] = intToString(rngHeight);
        thisBrick["life"] = intToString(rngLife);
        thisBrick["colour"] = rngColour;
        thisBrick["name"] = brickName;

        bricks.push_back(thisBrick);

    }


}

std::string Config::Config::intToString(int number) {
    std::stringstream stream;
    stream << number;
    return stream.str();
}


