#include "traffic_lights_controller.h"
#include "qdebug.h"
#include <QRandomGenerator>

traffic_lights_controller::traffic_lights_controller(QObject *parent)
    :QObject(parent), m_state(true)
{
    connect(&m_timer, &QTimer::timeout, this, &traffic_lights_controller::toggle);Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)
    int interval = QRandomGenerator::global()->bounded(5000, 8001);
    m_timer.start(interval);
}

void traffic_lights_controller::addIntersection(traffic_lights* north, traffic_lights* south,traffic_lights* east, traffic_lights* west)
{
    m_intersections.push_back({north, south, east, west});
    north->setState(m_state);
    south->setState(m_state);
    east->setState(!m_state);
    west->setState(!m_state);

}



QPointF traffic_lights_controller::getPosition()
{
    return m_position;
}

void traffic_lights_controller::setPosition(qreal x, qreal y)
{
    m_position = QPointF(x,y);
}



void traffic_lights_controller::toggle()
{
    m_state = !m_state;

    for (auto &i : m_intersections){
        i.north->setState(m_state);
        i.south->setState(m_state);
        i.east->setState(!m_state);
        i.west->setState(!m_state);
    }

    emit lightChanged(m_state, m_position);

    m_timer.start(QRandomGenerator::global()->bounded(3000, 5001));
}
