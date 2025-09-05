#ifndef CAR_H
#define CAR_H
#include "movingobject.h"
#include "traffic_lights_controller.h"

class car : public MovingObject
{
public:
    car(const std::vector<traffic_lights_controller*>& lights,
        QGraphicsItem* parent = nullptr);
    void move();
    void addControllers(std::vector<traffic_lights_controller*> c){controllers = c;};

public slots:
   void onLightChanged(bool greenForCars,QPointF interPos);
private:
   std::vector<traffic_lights_controller*> lights_Before_Car;
   qreal stop_distance = 50.0;
   QPointF stopAt;
    traffic_lights_controller* currentController = nullptr;
    std::vector<traffic_lights_controller*> controllers;

};

#endif // CAR_H
