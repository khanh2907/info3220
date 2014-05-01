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
    scene->addItem(ball);

    // brick layer with TAFE diploma
    std::vector< std::map<std::string, std::string> > bricks = *(config->getBricks());

    for (auto it = bricks.begin(); it != bricks.end(); ++it) {
        auto thisBrick = *(it);
        int xCoordinate = atoi(thisBrick["xCoordinate"].c_str());
        int yCoordinate = atoi(thisBrick["yCoordinate"].c_str());
        int width = atoi(thisBrick["width"].c_str());
        int height = atoi(thisBrick["height"].c_str());
        int life = atoi(thisBrick["life"].c_str());
        const char * colour = thisBrick["colour"].c_str();

        // check here if it's going to overlap with any other bricks before creating it

        QList<QGraphicsItem *> currentScene = scene->items();

        bool overlayValid = true;

        for (int i = 0; i < currentScene.count(); i++) {
            if (currentScene[i]->data(1) == "Ball")
                continue;

            Brick * otherBrick = dynamic_cast<Brick*>(currentScene[i]);

            qreal otherBrickLeft = otherBrick->pos().x();
            qreal otherBrickRight = otherBrick->pos().x() + otherBrick->getWidth();
            qreal otherBrickTop = otherBrick->pos().y();
            qreal otherBrickBottom = otherBrick->pos().y() + otherBrick->getHeight();

            if ((xCoordinate >= otherBrickLeft && xCoordinate <= otherBrickRight) ||
                    (xCoordinate + width >= otherBrickLeft && xCoordinate + width <= otherBrickRight)) {
                if ((yCoordinate >= otherBrickTop && yCoordinate <= otherBrickBottom) ||
                        (yCoordinate + height >= otherBrickTop && yCoordinate + height <= otherBrickBottom)) {
                    overlayValid = false;
                }
            }

        }

        if (!overlayValid)
            continue;

        Brick *brick = new Brick(xCoordinate, yCoordinate, width, height, life, colour);

        // Extension: create special bricks using decorators
        if (thisBrick["SLD"] == "SLD" || thisBrick["INV"] == "INV" || thisBrick["TEL"] == "TEL") {
            SlidingBrick *slidingBrick = NULL;
            InvincibleBrick *invBrick = NULL;

            if (thisBrick["SLD"] == "SLD") {
                slidingBrick = new SlidingBrick(brick);
            }

            if (thisBrick["INV"] == "INV") {
                if (slidingBrick != NULL)
                    invBrick = new InvincibleBrick(slidingBrick);
                else
                    invBrick = new InvincibleBrick(brick);
            }

            if (invBrick != NULL)
                scene->addItem(invBrick);
            else if (slidingBrick != NULL)
                scene->addItem(slidingBrick);

        }
        else {
            scene->addItem(brick);
        }
    }

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
