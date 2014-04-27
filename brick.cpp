#include "brick.h"

Brick::Brick() {

}

Brick::Brick(int xCoordinate, int yCoordinate, int width, int height, int life, const char * colour) :
    position(new QPoint(xCoordinate, yCoordinate)),
    m_width(width),
    m_height(height),
    m_life(life),
    m_colour(QColor(colour)),
    m_xVelocity(0)
{
    setPos(mapToScene(*position));
}

Brick::~Brick() {
    delete position;
}

QRectF Brick::boundingRect() const{
    return QRectF(0, 0, m_width, m_height);
}

void Brick::advance(int phase) {
    if (phase == 0){
      return;
    }

    if (m_life <= 0) {
        scene()->removeItem(this);
        this->deleteLater();
        return;
    }
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    QRectF rec = boundingRect();
    QBrush brush("#FFFFFF");
    brush.setColor(m_colour);

    painter->setBrush(brush);
    painter->drawRect(rec);
}

QPoint * Brick::getPosition() { return position;}
int Brick::getWidth() { return m_width;}
int Brick::getHeight() { return m_height;}
int Brick::getLife() { return m_life;}
QColor Brick::getColour() { return m_colour;}
int Brick::getXVelocity() { return m_xVelocity; }

int Brick::decrementLife() {
    m_life--;
    prepareGeometryChange();
    return m_life;
}
