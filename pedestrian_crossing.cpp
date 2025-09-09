#include "pedestrian_crossing.h"
#include "qbrush.h"
#include "qdebug.h"

pedestrian_crossing::pedestrian_crossing(QPointF pos)
{
    setRect(0, 0, 80, 25);
    //setRect(0, 0, 5, 5);
    position = pos;

    setBrush(QBrush(Qt::white));
    setPos(position);
    qDebug()<< position;
    stop1 = QPointF(position.x()-10, position.y() +15);
    stop2 = QPointF(position.x()+100, position.y() -15);
}
