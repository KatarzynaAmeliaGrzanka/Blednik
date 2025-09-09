#ifndef PEDESTRIAN_CROSSING_H
#define PEDESTRIAN_CROSSING_H
#include <QObject>
#include <QGraphicsRectItem>



#include "qpoint.h"

class pedestrian_crossing:   public QGraphicsRectItem{


public:
    pedestrian_crossing(QPointF position);
    void setOccupied() { Occupied = true; }
    void setEmpty() { Occupied = false; }
    bool isOccupied() { return Occupied;};
    QPointF getPosition() { return position;}
    QPointF getStop1() {return stop1; };
    QPointF getStop2() {return stop2; };
private:
    QPointF position;
    bool Occupied = false;
    QPointF stop1;
    QPointF stop2;
};

#endif // PEDESTRIAN_CROSSING_H
