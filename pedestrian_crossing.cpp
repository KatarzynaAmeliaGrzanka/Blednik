#include "pedestrian_crossing.h"
#include "qbrush.h"
#include "qdebug.h"

pedestrian_crossing::pedestrian_crossing(QPointF pos)
{
    setRect(0, 0, 80, 25);
    m_position = pos;

    setBrush(QBrush(Qt::white));
    setPos(m_position);
    qDebug()<< m_position;
    m_stop1 = QPointF(m_position.x()-10, m_position.y() +15);
    m_stop2 = QPointF(m_position.x()+100, m_position.y() -15);
}
