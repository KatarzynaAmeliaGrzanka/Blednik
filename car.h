#ifndef CAR_H
#define CAR_H
#include "intersection.h"
#include "movingobject.h"
#include "pedestrian_crossing.h"
#include "traffic_lights_controller.h"

class car : public QObject, public MovingObject {
        Q_OBJECT

public:
    enum CarState {
        DRIVING,
        APPROACHING,
        WAITING,
        TURNING,
        CROSSING,
        DECIDING,
        TURN_RIGHT,
        TURN_LEFT,
        WAITING_AT_CROSSING

    };

    car(Direction dir, const std::vector<intersection*>& intersections, const std::vector<pedestrian_crossing*>& crossings,
        QGraphicsItem* parent = nullptr);
    void move();
    void addControllers(std::vector<traffic_lights_controller*> c){controllers = c;};
    intersection* nearestIntersection(QPointF pos);
    pedestrian_crossing* nearestCrossing(QPointF pos);
    void goAhead();
    QPointF getStartOfIntersection(Direction dir);
public slots:
   void onLightChanged(bool greenForCars,QPointF interPos);
private:
   qreal stop_distance = 50.0;
   QPointF stopAt;
    traffic_lights_controller* currentController = nullptr;
    std::vector<traffic_lights_controller*> controllers;
    std::vector<pedestrian_crossing*> crossings;
    std::vector<intersection*> intersections;
    intersection* lastIntersection = nullptr;
    CarState state = DRIVING;
    QPointF startOfIntersection;
};

#endif // CAR_H
