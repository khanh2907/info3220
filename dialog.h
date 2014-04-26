#ifndef DIALOG_H
#define DIALOG_H

#include <QTimer>
#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <string>
#include "config.h"
#include "brick.h"
#include "invinciblebrick.h"
#include "ball.h"
#include "itemfactory.h"

namespace Ui{
class Dialog;
}

class Dialog : public QDialog{
    Q_OBJECT

public:
    explicit Dialog(Config::Config *config, QWidget *parent = 0);
    ~Dialog();

    QGraphicsScene * getScene(){ return scene; }

public slots:
    void nextFrame();

private:
    Ui::Dialog *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    Config::Config *config;
};

#endif // DIALOG_H
