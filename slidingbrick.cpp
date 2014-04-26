#include "slidingbrick.h"

void SlidingBrick::advance(int phase) {
    if (phase == 0){
      return;
    }

    if (this == NULL) {
        return;
    }

    int futureXPos =pos().x() + m_xVelocity;

    if (futureXPos <= 0) {
        futureXPos = 0;
        m_xVelocity *= -1;
    }

    else if (futureXPos + m_width >= scene()->width()) {
        futureXPos = scene()->width() - m_width;
        m_xVelocity *= -1;
    }

    setPos(futureXPos, pos().y());
}
