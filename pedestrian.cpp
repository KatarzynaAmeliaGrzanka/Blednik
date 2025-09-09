#include "pedestrian.h"

#include "qbrush.h"
#include "qdebug.h"
#include <QRandomGenerator>



pedestrian::pedestrian(Direction::direction dir, const std::vector<intersection *> &intersections, const std::vector<pedestrian_crossing*>& crossings, std::vector<QPointF> car_start_points, QGraphicsItem *parent)
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
                qDebug() << 5;
                state = APPROACHING;
            }

            double dx2 = nearestCrossing(pos())->getStop1().x() - pos().x();
            double dy2 = nearestCrossing(pos())->getStop1().y() - pos().y();
            double dxy2 = std::sqrt(dx2*dx2 + dy2*dy2);

            if (dxy2 < 30 && nearestCrossing(pos()) != lastCrossing){
                state = APPROACHING_CROSSING;
            }


        /*    dx2 = nearestCrossing(pos())->getStop2().x() - pos().x();
            dy2 = nearestCrossing(pos())->getStop2().y() - pos().y();
            dxy2 = std::sqrt(dx2*dx2 + dy2*dy2);


            if (dxy2 < 30 && nearestCrossing(pos()) != lastCrossing){
                state = APPROACHING_CROSSING;
            }
*/

        break;
    }
        case APPROACHING:
            setSpeed(1);
            lastIntersection = nearestIntersection(pos());
            if(getDirection() == Direction::RIGHT){
            if (std::abs(pos().x() - getTurnPoint())<1){
                setDirection(Direction::DOWN);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }
            }
            if(getDirection() == Direction::LEFT){
            if (std::abs(pos().x() - getTurnPoint())<0.5){
                setDirection(Direction::UP);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }
            }

            if(getDirection() == Direction::DOWN){
            if (std::abs(pos().y() - getTurnPoint())<0.5 && lastIntersection->getPosition().x() > pos().x()){
                setDirection(Direction::LEFT);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }

            else if (std::abs(pos().y() - getTurnPoint())<0.5 && lastIntersection->getPosition().x() < pos().x()){
                setDirection(Direction::RIGHT);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }
            }


            if(getDirection() == Direction::UP){
            if (std::abs(pos().y() - getTurnPoint())<0.5){
                setDirection(Direction::RIGHT);
                setSpeed(getDefaultSpeed());
                state = WALKING;
            }
            }


        break;

    case APPROACHING_CROSSING:
        setSpeed(1);

        if (distance(pos(), nearestCrossing(pos())->getStop1()) < 1){
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
               if(getDirection() == Direction::DOWN){
                  setDirection(Direction::RIGHT);
                  lastCrossing->setOccupied();
                  state = CROSSING;
               }

               if(getDirection() == Direction::UP){
                  setDirection(Direction::RIGHT);
                  state = CROSSING;
               }
           }


        break;

    case CROSSING:

       if (pos().x() == nearestCrossing(pos())->getStop2().x()){
           setDirection(Direction::UP);
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
        case Direction::RIGHT:
            setPos(p.x() + getSpeed(), p.y());
            if (x() > 1150) {
                lastIntersection = nullptr;
                setY(y() - 110);
                setDirection(Direction::LEFT);
            }
        break;

        case Direction::LEFT:
            setPos(p.x() - getSpeed(), p.y());
            if (x() < 1) {
                lastIntersection = nullptr;
                setY(y() + 110);
                setDirection(Direction::RIGHT);
            }
        break;

        case Direction::UP:
            setPos(p.x(), p.y() - getSpeed());
            if (y() < 1) {
                lastIntersection = nullptr;
                setX(x() - 110);
                setDirection(Direction::DOWN);
            }
        break;

        case Direction::DOWN:
            setPos(p.x(), p.y() + getSpeed());
            if (y() > 1150) {
                lastIntersection = nullptr;
                setX(x() + 110);
                setDirection(Direction::UP);
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
    if (getDirection() == Direction::RIGHT) stop = nearestIntersection(pos())->getPosition().x() - 50;
    if (getDirection() == Direction::LEFT) stop = nearestIntersection(pos())->getPosition().x() + 60;
    if (getDirection() == Direction::UP) stop = nearestIntersection(pos())->getPosition().y() + 60;
    if (getDirection() == Direction::DOWN) stop = nearestIntersection(pos())->getPosition().y() - 50;

    return stop;
}

