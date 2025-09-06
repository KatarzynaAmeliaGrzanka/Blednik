#ifndef CAR_H
#define CAR_H
#include "intersection.h"
#include "movingobject.h"
#include "traffic_lights_controller.h"

class car : public QObject, public MovingObject {
        Q_OBJECT

public:
    car(Direction dir, const std::vector<intersection*>& intersections,
        QGraphicsItem* parent = nullptr);
    void move();

    void addControllers(std::vector<traffic_lights_controller*> c){controllers = c;};
    void decideDirection();
    void turnRight();
    void leftOrStraight(intersection* i);
    void rightOrStraight(intersection* i);
    bool getTurning() {return turning;}
public slots:
   void onLightChanged(bool greenForCars,QPointF interPos);
private:
   std::vector<traffic_lights_controller*> lights_Before_Car;
   qreal stop_distance = 50.0;
   QPointF stopAt;
    traffic_lights_controller* currentController = nullptr;
    std::vector<traffic_lights_controller*> controllers;
    std::vector<intersection*> intersections;
    bool turning = false;
    bool turnedRightOrStraight = false;
    bool turnedLeftOrStraight = false;
    intersection* lastIntersection = nullptr;


};

#endif // CAR_H
