#include "pedestrian.h"

#include "qbrush.h"
#include "qdebug.h"
#include <QRandomGenerator>



pedestrian::pedestrian(Direction dir, const std::vector<intersection *> &intersections, const std::vector<pedestrian_crossing*>& crossings, std::vector<QPointF> car_start_points, QGraphicsItem *parent)
 :QObject(), MovingObject(), intersections(intersections), crossings(crossings), car_start_points(car_start_points)
{
    setRect(-10, -10, 10, 10);
    setBrush(QBrush(Qt::yellow));
    setSpeed(3.0);
    setDirection(dir);
}

void pedestrian::move()
{
    intersection *nearest_intersection;
    int choice;
    switch (state){
    case WALKING: {
        setSpeed(getDefaultSpeed());
            double dx = nearestIntersection(pos())->getPosition().x() - pos().x();
            double dy = nearestIntersection(pos())->getPosition().y() - pos().y();
            double dxy = std::sqrt(dx*dx + dy*dy);
            if (dxy < 100 && lastIntersection != nearestIntersection(pos())){
                qDebug() << 4;
                state = APPROACHING;
            }

            double dx2 = nearestCrossing(pos())->getStop1().x() - pos().x();
            double dy2 = nearestCrossing(pos())->getStop1().y() - pos().y();
            double dxy2 = std::sqrt(dx2*dx2 + dy2*dy2);

            if (dxy2 < 30 && nearestCrossing(pos()) != lastCrossing){
                state = APPROACHING_CROSSING;
            }


            dx2 = nearestCrossing(pos())->getStop2().x() - pos().x();
            dy2 = nearestCrossing(pos())->getStop2().y() - pos().y();
            dxy2 = std::sqrt(dx2*dx2 + dy2*dy2);


            if (dxy2 < 30 && nearestCrossing(pos()) != lastCrossing){
                state = APPROACHING_CROSSING;
            }


        break;
    }
        case APPROACHING:
            setSpeed(1);
            lastIntersection = nearestIntersection(pos());
            if(getDirection() == RIGHT){
            if (std::abs(pos().x() - getTurnPoint())<1){
                setDirection(DOWN);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }
            }
            if(getDirection() == LEFT){
            if (std::abs(pos().x() - getTurnPoint())<1){
                setDirection(UP);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }
            }

            if(getDirection() == DOWN){
            if (std::abs(pos().y() - getTurnPoint())<1 && lastIntersection->getPosition().x() > pos().x()){
                setDirection(LEFT);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }

            else if (std::abs(pos().y() - getTurnPoint())<1 && lastIntersection->getPosition().x() < pos().x()){
                setDirection(RIGHT);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }
            }


            if(getDirection() == UP){
            if (std::abs(pos().y() - getTurnPoint())<1){
                setDirection(RIGHT);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }
            }


        break;

    case APPROACHING_CROSSING:
        setSpeed(1);

        choice = QRandomGenerator::global()->bounded(2);



        if (distance(pos(), nearestCrossing(pos())->getStop1()) < 1 || distance(pos(), nearestCrossing(pos())->getStop1()) < 1){
            state = DECIDING;
        }



        break;

    case DECIDING:
        choice = QRandomGenerator::global()->bounded(2); //0 - prosto, 1 - skręca
        lastCrossing = nearestCrossing(pos());

           if (choice == 0){
               setSpeed(getDefaultSpeed());
               state = WALKING;
           }

           else if(choice == 1){
               if(getDirection() == DOWN){
                  setDirection(RIGHT);
                  lastCrossing->setOccupied();
                  state = CROSSING;
               }

               if(getDirection() == UP){
                  setDirection(RIGHT);
                  state = CROSSING;
               }
           }


        break;

    case CROSSING:

       if (pos().x() == nearestCrossing(pos())->getStop2().x()){
           setDirection(UP);
           //lastCrossing = nullptr;
           lastIntersection = nullptr;
           setSpeed(getDefaultSpeed());
           lastCrossing->setEmpty();
           state = WALKING;
       }
        break;

       }





    goAhead();
}

void pedestrian::goAhead()
{
    QPointF p = pos();
    switch(getDirection()) {
        case RIGHT:
            setPos(p.x() + getSpeed(), p.y());
            if (x() > 1150) {
                lastIntersection = nullptr;
                setY(y() - 110);
                setDirection(LEFT);
            }
        break;

        case LEFT:
            setPos(p.x() - getSpeed(), p.y());
            if (x() < 1) {
                lastIntersection = nullptr;
                setY(y() + 110);
                setDirection(RIGHT);
            }
        break;

        case UP:
            setPos(p.x(), p.y() - getSpeed());
            if (y() < 1) {
                lastIntersection = nullptr;
                setX(x() - 110);
                setDirection(DOWN);
            }
        break;

        case DOWN:
            setPos(p.x(), p.y() + getSpeed());
            if (y() > 1150) {
                lastIntersection = nullptr;
                setX(x() + 110);
                setDirection(UP);
            }
        break;


    }

}

intersection *pedestrian::nearestIntersection(QPointF pos)
{
    double minDist = 1e9;
           intersection* nearest_intersection = nullptr;

           // find nearest intersection
           for (auto* i : intersections){
               double dx = i->getPosition().x() - pos.x();
               double dy = i->getPosition().y() - pos.y();
               double dxy = std::sqrt(dx*dx + dy*dy);

               if (dxy < minDist){
                       minDist = dxy;
                       nearest_intersection = i;
               }
           }
     return nearest_intersection;

}

pedestrian_crossing *pedestrian::nearestCrossing(QPointF pos)
{
    double minDist = 1e9;
           pedestrian_crossing* nearest_crossing = nullptr;

           // find nearest intersection
           for (auto* i : crossings){
               double dx = i->getPosition().x() - pos.x();
               double dy = i->getPosition().y() - pos.y();
               double dxy = std::sqrt(dx*dx + dy*dy);

               if (dxy < minDist){
                       minDist = dxy;
                       nearest_crossing = i;
               }
           }
           return nearest_crossing;
}

qreal pedestrian::distance(QPointF a, QPointF b)
{
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return std::sqrt(dx*dx + dy*dy);
}

int pedestrian::getTurnPoint()
{
    int stop = 0;
    if (getDirection() == RIGHT) stop = nearestIntersection(pos())->getPosition().x() - 50;
    if (getDirection() == LEFT) stop = nearestIntersection(pos())->getPosition().x() + 50;
    if (getDirection() == UP) stop = nearestIntersection(pos())->getPosition().y() + 60;
    if (getDirection() == DOWN) stop = nearestIntersection(pos())->getPosition().y() - 50;

    return stop;
}

