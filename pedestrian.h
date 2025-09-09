#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "intersection.h"
#include "movingobject.h"
#include "pedestrian_crossing.h"


class pedestrian : public QObject, public MovingObject {
    Q_OBJECT
    enum PedestrianState {
        WALKING,
        APPROACHING,
        WAITING,
        TURNING,
        CROSSING,
        DECIDING,
        TURN_RIGHT,
        TURN_LEFT,
        APPROACHING_CROSSING
    };
public:
    pedestrian(Direction dir, const std::vector<intersection*>& intersections, const std::vector<pedestrian_crossing*>& crossings, std::vector<QPointF> car_start_points,
               QGraphicsItem* parent = nullptr);
    void move();
    void goAhead();
    intersection * nearestIntersection(QPointF pos);
    pedestrian_crossing* nearestCrossing(QPointF pos);
    qreal distance(QPointF a, QPointF b);


    int getTurnPoint();

private:
    PedestrianState state = WALKING;
    std::vector<intersection*> intersections;
    std::vector<pedestrian_crossing*> crossings;
    intersection* lastIntersection = nullptr;
    pedestrian_crossing* lastCrossing = nullptr;
    std::vector<QPointF> car_start_points;

};

#endif // PEDESTRIAN_H
