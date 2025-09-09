#include "car.h"
#include "qbrush.h"
#include "qdebug.h"
#include <QRandomGenerator>

#include <QPropertyAnimation>
#include <QEasingCurve>



car::car(Direction::direction dir, const std::vector<intersection *> &intersections, const std::vector<pedestrian_crossing*>& crossings, QGraphicsItem *parent)
    :QObject(), MovingObject(), crossings(crossings), intersections(intersections)
{
    setRect(-10, -10, 20, 20);
    setBrush(QBrush(Qt::lightGray));
    setSpeed(3.0);
    setDirection(dir);

}

void car::move()
{
    QPointF posNow = pos();
    traffic_lights_controller* nearest_controller = nullptr;
    intersection* nearest_intersection = nullptr;
    pedestrian_crossing* nearest_crossing = nullptr;
    int stop = 0;
    int choice;


    switch (state){
    case DRIVING:
        nearest_intersection = nearestIntersection(posNow);
        nearest_crossing = nearestCrossing(posNow);

        setSpeed(getDefaultSpeed());
        if(nearest_intersection && nearest_intersection->hasLights() && nearest_intersection->getController() != currentController){
            double dx = nearest_intersection->getPosition().x() - posNow.x();
            double dy =nearest_intersection->getPosition().y() - posNow.y();
            double dxy = std::sqrt(dx*dx + dy*dy);

            if (dxy < 100){
                lastIntersection = nullptr;
                state = APPROACHING;
            }

        }

       if (nearest_crossing && nearest_crossing->isOccupied()){
            double dx = nearest_crossing->getPosition().x() - posNow.x();
            double dy = nearest_crossing->getPosition().y() - posNow.y();
            double dxy = std::sqrt(dx*dx + dy*dy);

            if (dxy < 100){
                qDebug()<< "pieszy na pasach";
                state = WAITING_AT_CROSSING;
                setSpeed(0);
            }
        }

        if(!nearest_intersection->hasLights() && lastIntersection != nearest_intersection){

            double dx = nearest_intersection->getPosition().x() - posNow.x();
            double dy = nearest_intersection->getPosition().y() - posNow.y();
            double dxy = std::sqrt(dx*dx + dy*dy);

            if (dxy < 60){
                lastIntersection = nearest_intersection;

                setSpeed(1);
                startOfIntersection = getStartOfIntersection(getDirection());
                if (lastIntersection && lastIntersection ->isOccupied()){
                    setSpeed(0);
                    qDebug()<<"heree";
                    state = WAITING_TO_CROSS;
                }
                else{state = DECIDING;}
            }
        }
        break;

    case  APPROACHING:
        setSpeed(1);

        currentController = nearestIntersection(pos())->getController();

        connect(currentController, &traffic_lights_controller::lightChanged,
                                   this, &car::onLightChanged);

                      if (this->getDirection()==Direction::RIGHT) {
                          stop = nearestIntersection(pos())->getPosition().x()-50;
                          startOfIntersection = QPointF( stop, posNow.y());
                      }
                      if (this->getDirection()==Direction::LEFT){
                          stop = nearestIntersection(pos())->getPosition().x()+50;
                          startOfIntersection = QPointF( stop, posNow.y());
                      }
                      if (this->getDirection()==Direction::UP){

                          stop = nearestIntersection(pos())->getPosition().y()+50;
                          startOfIntersection = QPointF( posNow.x(), stop);
                      }
                      if (this->getDirection()==Direction::DOWN){
                          stop = nearestIntersection(pos())->getPosition().y()-50;
                          startOfIntersection = QPointF( posNow.x(), stop);
                      }

                     if (getDirection() == Direction::RIGHT || getDirection() == Direction::LEFT){
                          if(std::abs(posNow.x() - stop) < 0.5){
                              if( !currentController->getState()) {
                              state = WAITING;
                              }

                              else {
                                  if(nearestIntersection(pos())->isOccupied()){
                                      setSpeed(0);
                                        state = WAITING_TO_CROSS;
                                  }
                                  else {
                                      state = DECIDING;
                                  setSpeed(1);}
                              }
                          }
                     }

                     if (getDirection() == Direction::UP || getDirection() == Direction::DOWN){
                          if(std::abs(posNow.y() - stop) < 0.5){
                              if( currentController->getState()) {
                              state = WAITING;
                              }


                              else {
                                  if(nearestIntersection(pos())->isOccupied()){
                                      setSpeed(0);
                                      state = WAITING_TO_CROSS;
                                  }
                                  else{
                                  state = DECIDING;
                                  setSpeed(1);}
                              }
                          }
                     }

        break;

     case WAITING_TO_CROSS:
        qDebug()<< "heree2";
        qDebug() << nearestCrossing(pos())->isOccupied();

        if (!nearestIntersection(pos())->isOccupied()){
                setSpeed(1);
                qDebug()<<"here";
                state = DECIDING;
         }
        break;


    case WAITING_AT_CROSSING:
        if (!nearestCrossing(pos())->isOccupied()){
            setSpeed(getDefaultSpeed());
            state = DRIVING;
        }
        break;

    case DECIDING:
    lastIntersection = nearestIntersection(pos());
    lastIntersection->setOccupied();

       choice = QRandomGenerator::global()->bounded(3); // 0 prosto 1 lewo 2 prawo
       if (choice == 1) state = TURN_RIGHT;
       if (choice == 2) state = TURN_LEFT;
       if (choice == 0 ) {
           nearestIntersection(pos())->setEmpty();
           setSpeed(getDefaultSpeed());
           state = DRIVING;}

       break;

     case TURN_RIGHT:

        if (getDirection() == Direction::RIGHT){
            if (pos().x() == startOfIntersection.x() +30){
                setDirection(Direction::DOWN);
                setSpeed(getDefaultSpeed());
                nearestIntersection(pos())->setEmpty();
                state = DRIVING;
            }
        }

        if (getDirection() == Direction::LEFT){
            if (pos().x() == startOfIntersection.x() -30){
                setDirection(Direction::UP);
                setSpeed(getDefaultSpeed());
                nearestIntersection(pos())->setEmpty();
                state = DRIVING;
            }
        }

        if (getDirection() ==Direction::UP){
            if (pos().y() == startOfIntersection.y() -30){
                setDirection(Direction::RIGHT);
                setSpeed(getDefaultSpeed());
                nearestIntersection(pos())->setEmpty();
                state = DRIVING;
            }
        }

        if (getDirection() == Direction::DOWN){
            if (pos().y() == startOfIntersection.y() +30){
                setDirection(Direction::LEFT);
                setSpeed(getDefaultSpeed());
                nearestIntersection(pos())->setEmpty();
                state = DRIVING;
            }
        }


        break;

    case TURN_LEFT:

        if (getDirection() == Direction::RIGHT){
           if (pos().x() == startOfIntersection.x() +75){
               setDirection(Direction::UP);
               setSpeed(getDefaultSpeed());
               nearestIntersection(pos())->setEmpty();
               state = DRIVING;
           }
        }
        if (getDirection() == Direction::LEFT){
           if (pos().x() == startOfIntersection.x() -75){
               setDirection(Direction::DOWN);
               setSpeed(getDefaultSpeed());
               nearestIntersection(pos())->setEmpty();
               state = DRIVING;
           }
        }

        if (getDirection() == Direction::UP){
           if (pos().y() == startOfIntersection.y() -75){
               setDirection(Direction::LEFT);
               setSpeed(getDefaultSpeed());
               nearestIntersection(pos())->setEmpty();
               state = DRIVING;
           }
        }

        if (getDirection() == Direction::DOWN){
           if (pos().y() == startOfIntersection.y() +75){
               setDirection(Direction::RIGHT);
               setSpeed(getDefaultSpeed());
               nearestIntersection(pos())->setEmpty();
               state = DRIVING;
           }
        }
       break;

   case WAITING:

        setSpeed(0);
        if (getDirection() == Direction::RIGHT || getDirection() == Direction::LEFT){
        if( currentController->getState()) {

           setSpeed(1);
           state = DECIDING;
        }
        }
        if (getDirection() == Direction::UP || getDirection() == Direction::DOWN){
        if( !currentController->getState()) {

           setSpeed(1);
           state = DECIDING;
        }
        }

        break;
  case CROSSING:


       if (pos().x() > startOfIntersection.x() + 75)
       {
           state = DRIVING;
}

        break;



}
    goAhead();

}








intersection *car::nearestIntersection(QPointF pos)
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

pedestrian_crossing *car::nearestCrossing(QPointF pos)
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

void car::goAhead()
{
    QPointF p = pos();
    switch(getDirection()) {
        case Direction::RIGHT:
            setPos(p.x() + getSpeed(), p.y());
            if (x() > 1150) {
                currentController = nullptr;
                lastIntersection = nullptr;
                //speed = -speed;
                //default_speed = speed;
                setY(y() - 40);
                setDirection(Direction::LEFT);
            }
        break;

        case Direction::LEFT:
            setPos(p.x() - getSpeed(), p.y());
            if (x() < 1) {
                currentController = nullptr;
                lastIntersection = nullptr;
                //speed = -speed;
                //default_speed = speed;
                setY(y() + 40);
                setDirection(Direction::RIGHT);
            }
        break;

        case Direction::UP:
            setPos(p.x(), p.y() - getSpeed());
            if (y() < 1) {
                lastIntersection = nullptr;
                currentController = nullptr;
                //speed = -speed;
                //default_speed = speed;
                setX(x() - 40);
                setDirection(Direction::DOWN);
            }
        break;

        case Direction::DOWN:
            setPos(p.x(), p.y() + getSpeed());
            if (y() > 1150) {
                currentController = nullptr;
                lastIntersection = nullptr;
                //speed = -speed;
                //default_speed = speed;
                setX(x() + 40);
                setDirection(Direction::UP);
            }
        break;


    }

}

QPointF car::getStartOfIntersection(Direction::direction dir)
{
    int stop;
    if (this->getDirection()==Direction::RIGHT) {
        stop = nearestIntersection(pos())->getPosition().x()-50;
        startOfIntersection = QPointF( stop, pos().y());
    }
    if (this->getDirection()==Direction::LEFT){
        stop = nearestIntersection(pos())->getPosition().x()+50;
        startOfIntersection = QPointF( stop, pos().y());
    }
    if (this->getDirection()==Direction::UP){

        stop = nearestIntersection(pos())->getPosition().y()+50;
        startOfIntersection = QPointF( pos().x(), stop);
    }
    if (this->getDirection()==Direction::DOWN){
        stop = nearestIntersection(pos())->getPosition().y()-50;
        startOfIntersection = QPointF( pos().x(), stop);
    }

    return startOfIntersection;
}

void car::onLightChanged(bool greenForCars,QPointF interPos)
{
    if(this->getDirection() == Direction::RIGHT || this->getDirection() == Direction::LEFT){
        if (qFuzzyCompare(stopAt.x(), interPos.x()) &&
                qFuzzyCompare(stopAt.y(), interPos.y()))
            {
                if (greenForCars) {
             //       qDebug() << "🚗 Ruszam, bo zielone!";
                    QTimer::singleShot(2000, this, [this]() {
                        setSpeed(getDefaultSpeed());
                        if (currentController) {
                                        disconnect(currentController, nullptr, this, nullptr);
                                        currentController = nullptr;
                                    }
                        currentController = nullptr; // już przejechał
                    });

                } else {
             //       qDebug() << "🚗 Stoję, czerwone.";
                }
            }
    }

    if(this->getDirection() == Direction::UP || this->getDirection() == Direction::DOWN){
        if (qFuzzyCompare(stopAt.x(), interPos.x()) &&
                qFuzzyCompare(stopAt.y(), interPos.y()))
            {
                if (!greenForCars) {
             //       qDebug() << "🚗 Ruszam, bo zielone!";
                    QTimer::singleShot(2000, this, [this]() {
                        setSpeed(getDefaultSpeed());
                        if (currentController) {
                                        disconnect(currentController, nullptr, this, nullptr);
                                        currentController = nullptr;
                                    }
                        currentController = nullptr; // już przejechał
                    });
                } else {
               //     qDebug() << "🚗 Stoję, czerwone.";
                }
            }
    }

}

