#ifndef INTERSECTION_H
#define INTERSECTION_H


#include "qpoint.h"
#include "traffic_lights_controller.h"
class intersection
{
public:
public:
    intersection(QPointF pos, traffic_lights_controller* controller = nullptr)
        : position(pos), controller(controller){}

    QPointF getPosition() const { return position; }
    traffic_lights_controller* getController() const {return controller;}
    bool hasLights() const {return controller != nullptr; }
    void addController(traffic_lights_controller* tctr) {controller = tctr;}

private:
    QPointF position;
    traffic_lights_controller* controller;
};

#endif // INTERSECTION_H
