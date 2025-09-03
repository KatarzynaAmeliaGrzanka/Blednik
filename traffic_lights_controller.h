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
   void addPairOfLight(traffic_lights* a, traffic_lights* b);
public slots:
    void toggle();
private:
    QTimer timer;
    bool state;
    std::vector<std::pair<traffic_lights*, traffic_lights* >> pairA;
    std::vector<std::pair<traffic_lights*, traffic_lights* >> pairB;

};

#endif // TRAFFIC_LIGHTS_CONTROLLER_H
