#include "dialog.h"
#include "config.h"
#include <QApplication>

int main(int argc, char *argv[]){
    Config::Config *config = new Config::Config();
    QApplication a(argc, argv);
    Dialog w(config);

    w.setFixedSize(config->getWidth(), config->getHeight());
    w.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), w.getScene(), SLOT(advance()));
    timer.start(1000 / 32);

    delete config;
    return a.exec();
}
