#include "traffic_lights.h"
#include <QBrush>



traffic_lights::traffic_lights(QGraphicsItem *parent)
    : QObject(), QGraphicsEllipseItem(parent), m_isGreen(true)
{
    setRect(0,0,20, 20);
    setBrush(QBrush(Qt::green));

}

void traffic_lights::setState(bool green) {
    m_isGreen = green;

    if (m_isGreen)
            setBrush(QBrush(Qt::green));
        else
        setBrush(QBrush(Qt::red));
}

bool traffic_lights::getState()
{
    return m_isGreen;
}
