#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <QGraphicsRectItem>
#include <QObject>


class MovingObject : public QObject, public QGraphicsRectItem {
public:
    MovingObject();
};

#endif // MOVINGOBJECT_H
