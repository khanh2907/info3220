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
