#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <QGraphicsRectItem>
#include <QObject>
#include "traffic_lights.h"


class MovingObject : public QObject, public QGraphicsRectItem {
public:
    MovingObject();
    void setSpeed(qreal s);
    qreal getDefaultSpeed() {return default_speed;}
public slots:
    void move();
private:
    qreal speed;
    qreal default_speed = 2;
};

#endif // MOVINGOBJECT_H
