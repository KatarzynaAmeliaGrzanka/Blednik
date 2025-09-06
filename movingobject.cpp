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
    QPointF p = pos();

    switch(direction) {
        case RIGHT:
            setPos(p.x() + speed, p.y());
            if (x() > 1150) {
                //speed = -speed;
                //default_speed = speed;
                setY(y() - 40);
                direction = LEFT;
            }
        break;

        case LEFT:
            setPos(p.x() - speed, p.y());
            if (x() < 1) {
                //speed = -speed;
                //default_speed = speed;
                setY(y() + 40);
                direction = RIGHT;
            }
        break;

        case UP:
            setPos(p.x(), p.y() - speed);
            if (y() < 1) {
                //speed = -speed;
                //default_speed = speed;
                setX(x() - 40);
                direction = DOWN;
            }
        break;

        case DOWN:
            setPos(p.x(), p.y() + speed);
            if (y() > 1150) {
                //speed = -speed;
                default_speed = speed;
                setX(x() + 40);
                direction = UP;
            }
        break;


    }


}


