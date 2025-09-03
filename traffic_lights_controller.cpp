#include "traffic_lights_controller.h"
#include <QRandomGenerator>

traffic_lights_controller::traffic_lights_controller(QObject *parent)
    :QObject(parent), state(true)
{
    connect(&timer, &QTimer::timeout, this, &traffic_lights_controller::toggle);Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)
    int interval = QRandomGenerator::global()->bounded(5000, 8001);
    timer.start(interval);
}

void traffic_lights_controller::addPairOfLight(traffic_lights *a, traffic_lights *b)
{
    if (pairA.empty())
            pairA.push_back({a, b}); // pierwsza para = A
        else
        pairB.push_back({a, b}); // druga para = B
}

void traffic_lights_controller::toggle()
{
    state = !state;

    for (auto &pair : pairA){
        pair.first->setState(state);
        pair.second->setState(state);
    }

    for (auto &pair : pairB){
        pair.first->setState(!state);
        pair.second->setState(!state);
    }
}
