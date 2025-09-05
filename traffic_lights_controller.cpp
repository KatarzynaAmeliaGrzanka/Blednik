#include "traffic_lights_controller.h"
#include "qdebug.h"
#include <QRandomGenerator>

traffic_lights_controller::traffic_lights_controller(QObject *parent)
    :QObject(parent), state(true)
{
    connect(&timer, &QTimer::timeout, this, &traffic_lights_controller::toggle);Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)
    int interval = QRandomGenerator::global()->bounded(5000, 8001);
    timer.start(interval);
}

void traffic_lights_controller::addIntersection(traffic_lights* north, traffic_lights* south,traffic_lights* east, traffic_lights* west)
{
    /*if (pairA.empty())
            pairA.push_back({a, b}); // pierwsza para = A
        else
        pairB.push_back({a, b}); // druga para = B*/
    intersections.push_back({north, south, east, west});
    north->setState(state);
    south->setState(state);
    east->setState(!state);
    west->setState(!state);


}

traffic_lights *traffic_lights_controller::getWest()
{
    for (auto &i : intersections){
        qDebug() << "Droga" ;
        return i.north;
   }

}

QPointF traffic_lights_controller::getPosition()
{
    return position;
}

void traffic_lights_controller::setPosition(qreal x, qreal y)
{
    position = QPointF(x,y);
}



void traffic_lights_controller::toggle()
{
    state = !state;

    for (auto &i : intersections){
        i.north->setState(state);
        i.south->setState(state);
        i.east->setState(!state);
        i.west->setState(!state);
    }

    emit lightChanged(state, position);

    timer.start(QRandomGenerator::global()->bounded(3000, 5001));
}
