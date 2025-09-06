#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <QGraphicsRectItem>
#include <QObject>
#include "traffic_lights.h"


class MovingObject :  public QGraphicsRectItem {

public:
    MovingObject();

    enum Direction{ UP, DOWN, LEFT, RIGHT, RIGHT_DOWN};

    void setSpeed(qreal s);
    qreal getDefaultSpeed() {return default_speed;}

    void setDirection(Direction d) {direction = d;};
    Direction getDirection() const {return direction; }

public slots:
    void move();

private:
    qreal speed;
    qreal default_speed = 3;
    Direction direction = RIGHT;
};

#endif // MOVINGOBJECT_H
