#include "movingobject.h"

MovingObject::MovingObject()
{

}

void MovingObject::setSpeed(qreal s)
{
    speed = s;
}

void MovingObject::move()
{
    setX(x() + speed);

    if (x() < 1) {
        speed = -speed;
        default_speed = speed;
        setY(y() + 40);
    }
    if (x() > 1150) {
        speed = -speed;
        default_speed = speed;
        setY(y() - 40);

    }
}


