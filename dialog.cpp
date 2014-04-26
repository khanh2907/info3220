#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(Config::Config *config, QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog), config(config){
    ui->setupUi(this);

    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    view->setScene(scene);
    scene->setSceneRect(0, 0, config->getWidth(), config->getHeight());

    Ball *ball = dynamic_cast<Ball*>(ItemFactory::make("ball", config));

    std::vector< std::map<std::string, std::string> > bricks = *(config->getBricks());

    for (auto it = bricks.begin(); it != bricks.end(); ++it) {
        auto thisBrick = *(it);
        int xCoordinate = atoi(thisBrick["xCoordinate"].c_str());
        int yCoordinate = atoi(thisBrick["yCoordinate"].c_str());
        int width = atoi(thisBrick["width"].c_str());
        int height = atoi(thisBrick["height"].c_str());
        int life = atoi(thisBrick["life"].c_str());
        const char * colour = thisBrick["colour"].c_str();

        Brick *brick = new Brick(xCoordinate, yCoordinate, width, height, life, colour);
        scene->addItem(brick);
    }

    InvincibleBrick *invincibleBrick = new InvincibleBrick(new Brick(300, 500, 70, 20, 5, "#FFFFFF"));

    scene->addItem(invincibleBrick);

//    SlidingBrick *slidingBrick = new SlidingBrick(new Brick(0, 0, 70, 20, 1, "#02bbf8"));
//    scene->addItem(slidingBrick);

    scene->addItem(ball);

}

void Dialog::nextFrame(){
    update();
}

Dialog::~Dialog(){
    delete ui;
    delete view;
    //when deleting scene, scene also deletes all other items associated with the scene (i.e the ball)
    delete scene;
}
