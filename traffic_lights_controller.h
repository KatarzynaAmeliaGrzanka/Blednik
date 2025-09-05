#ifndef TRAFFIC_LIGHTS_CONTROLLER_H
#define TRAFFIC_LIGHTS_CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <vector>
#include "traffic_lights.h"

class traffic_lights_controller : public QObject
{
    Q_OBJECT
public:
   explicit traffic_lights_controller(QObject* parent = nullptr);
   void addIntersection(traffic_lights* north, traffic_lights* south,traffic_lights* east, traffic_lights* west);
   traffic_lights* getWest();
   QPointF getPosition();
   void setPosition(qreal x, qreal y);
   bool getState(){return state;} // stan dla całego skrzyzowania

signals:
   void lightChanged(bool carGreen, QPointF position);

public slots:
    void toggle();

private:
    struct Intesection{
        traffic_lights* north;
        traffic_lights* south;
        traffic_lights* east;
        traffic_lights* west;
    };
    std::vector<Intesection> intersections;
    QTimer timer;
    bool state = true;
    QPointF position;
   // std::vector<std::pair<traffic_lights*, traffic_lights* >> pairA;
   // std::vector<std::pair<traffic_lights*, traffic_lights* >> pairB;

};

#endif // TRAFFIC_LIGHTS_CONTROLLER_H
