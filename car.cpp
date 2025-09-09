#include "car.h"
#include "qbrush.h"
#include "qdebug.h"
#include <QRandomGenerator>

#include <QPropertyAnimation>
#include <QEasingCurve>



car::car(Direction dir, const std::vector<intersection *> &intersections, const std::vector<pedestrian_crossing*>& crossings, QGraphicsItem *parent)
    :QObject(), MovingObject(), crossings(crossings), intersections(intersections)
{
    setRect(-10, -10, 20, 20);
    setBrush(QBrush(Qt::red));
    setSpeed(3.0);
    setDirection(dir);

}

void car::move()
{
    QPointF posNow = pos();
    traffic_lights_controller* nearest_controller = nullptr;
    int stop = 0;
    int choice;


    switch (state){
    case DRIVING:

        setSpeed(getDefaultSpeed());
        if(nearestIntersection(posNow)->hasLights() && nearestIntersection(pos())->getController() != currentController){
            double dx = nearestIntersection(posNow)->getPosition().x() - posNow.x();
            double dy = nearestIntersection(posNow)->getPosition().y() - posNow.y();
            double dxy = std::sqrt(dx*dx + dy*dy);

            if (dxy < 100){
                lastIntersection = nullptr;
                state = APPROACHING;
            }

        }

       if (nearestCrossing(pos()) && nearestCrossing(pos())->isOccupied()){
            double dx = nearestCrossing(pos())->getPosition().x() - posNow.x();
            double dy = nearestCrossing(pos())->getPosition().y() - posNow.y();
            double dxy = std::sqrt(dx*dx + dy*dy);

            if (dxy < 50){
                qDebug()<< "pieszy na pasach";
              //  state = WAITING;
                setSpeed(0);
            }
        }

        if(!nearestIntersection(posNow)->hasLights() && lastIntersection != nearestIntersection(posNow)){

            double dx = nearestIntersection(posNow)->getPosition().x() - posNow.x();
            double dy = nearestIntersection(posNow)->getPosition().y() - posNow.y();
            double dxy = std::sqrt(dx*dx + dy*dy);

            if (dxy < 100){
                setSpeed(1);
                this->lastIntersection = nearestIntersection(posNow);
                startOfIntersection = getStartOfIntersection(getDirection());
                state = DECIDING;
            }
        }
        break;

    case  APPROACHING:
        setSpeed(1);

        currentController = nearestIntersection(pos())->getController();

        connect(currentController, &traffic_lights_controller::lightChanged,
                                   this, &car::onLightChanged);

                      if (this->getDirection()==RIGHT) {
                          stop = nearestIntersection(pos())->getPosition().x()-50;
                          startOfIntersection = QPointF( stop, posNow.y());
                      }
                      if (this->getDirection()==LEFT){
                          stop = nearestIntersection(pos())->getPosition().x()+50;
                          startOfIntersection = QPointF( stop, posNow.y());
                      }
                      if (this->getDirection()==UP){

                          stop = nearestIntersection(pos())->getPosition().y()+50;
                          startOfIntersection = QPointF( posNow.x(), stop);
                      }
                      if (this->getDirection()==DOWN){
                          stop = nearestIntersection(pos())->getPosition().y()-50;
                          startOfIntersection = QPointF( posNow.x(), stop);
                      }

                     if (getDirection() == RIGHT || getDirection() == LEFT){
                          if(posNow.x() == stop){
                              if( !currentController->getState()) {
                              state = WAITING;
                              }

                              else {state = DECIDING;setSpeed(1);}
                          }
                     }

                     if (getDirection() == UP || getDirection() == DOWN){
                          if(posNow.y() == stop){
                              if( currentController->getState()) {
                              state = WAITING;
                              }


                              else {state = DECIDING;setSpeed(1);}
                          }
                     }

        break;
    case WAITING_AT_CROSSING:
        if (!nearestCrossing(pos())->isOccupied()){
            state = DRIVING;
        }
        break;

    case DECIDING:
    lastIntersection = nearestIntersection(pos());

       choice = 1;//QRandomGenerator::global()->bounded(3); // 0 prosto 1 lewo 2 prawo
       if (choice == 1) state = TURN_RIGHT;
       if (choice == 2) state = TURN_LEFT;
       if (choice == 0 ) {
           setSpeed(getDefaultSpeed());
           state = DRIVING;}

       break;

     case TURN_RIGHT:

        if (getDirection() == RIGHT){
            if (pos().x() == startOfIntersection.x() +30){
                setDirection(DOWN);
                setSpeed(getDefaultSpeed());
                state = DRIVING;
            }
        }

        if (getDirection() == LEFT){
            if (pos().x() == startOfIntersection.x() -30){
                setDirection(UP);
                setSpeed(getDefaultSpeed());
                state = DRIVING;
            }
        }

        if (getDirection() == UP){
            if (pos().y() == startOfIntersection.y() -30){
                setDirection(RIGHT);
                setSpeed(getDefaultSpeed());
                state = DRIVING;
            }
        }

        if (getDirection() == DOWN){
            if (pos().y() == startOfIntersection.y() +30){
                setDirection(LEFT);
                setSpeed(getDefaultSpeed());
                state = DRIVING;
            }
        }


        break;

    case TURN_LEFT:

        if (getDirection() == RIGHT){
           if (pos().x() == startOfIntersection.x() +75){
               setDirection(UP);
               setSpeed(getDefaultSpeed());
               state = DRIVING;
           }
        }
        if (getDirection() == LEFT){
           if (pos().x() == startOfIntersection.x() -75){
               setDirection(DOWN);
               setSpeed(getDefaultSpeed());
               state = DRIVING;
           }
        }

        if (getDirection() == UP){
           if (pos().y() == startOfIntersection.y() -75){
               setDirection(LEFT);
               setSpeed(getDefaultSpeed());
               state = DRIVING;
           }
        }

        if (getDirection() == DOWN){
           if (pos().y() == startOfIntersection.y() +75){
               setDirection(RIGHT);
               setSpeed(getDefaultSpeed());
               state = DRIVING;
           }
        }
       break;

   case WAITING:

        setSpeed(0);
        if (getDirection() == RIGHT || getDirection() == LEFT){
        if( currentController->getState()) {

           setSpeed(1);
           state = DECIDING;
        }
        }
        if (getDirection() == UP || getDirection() == DOWN){
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
        case RIGHT:
            setPos(p.x() + getSpeed(), p.y());
            if (x() > 1150) {
                currentController = nullptr;
                lastIntersection = nullptr;
                //speed = -speed;
                //default_speed = speed;
                setY(y() - 40);
                setDirection(LEFT);
            }
        break;

        case LEFT:
            setPos(p.x() - getSpeed(), p.y());
            if (x() < 1) {
                currentController = nullptr;
                lastIntersection = nullptr;
                //speed = -speed;
                //default_speed = speed;
                setY(y() + 40);
                setDirection(RIGHT);
            }
        break;

        case UP:
            setPos(p.x(), p.y() - getSpeed());
            if (y() < 1) {
                lastIntersection = nullptr;
                currentController = nullptr;
                //speed = -speed;
                //default_speed = speed;
                setX(x() - 40);
                setDirection(DOWN);
            }
        break;

        case DOWN:
            setPos(p.x(), p.y() + getSpeed());
            if (y() > 1150) {
                currentController = nullptr;
                lastIntersection = nullptr;
                //speed = -speed;
                //default_speed = speed;
                setX(x() + 40);
                setDirection(UP);
            }
        break;


    }

}

QPointF car::getStartOfIntersection(Direction dir)
{
    int stop;
    if (this->getDirection()==RIGHT) {
        stop = nearestIntersection(pos())->getPosition().x()-50;
        startOfIntersection = QPointF( stop, pos().y());
    }
    if (this->getDirection()==LEFT){
        stop = nearestIntersection(pos())->getPosition().x()+50;
        startOfIntersection = QPointF( stop, pos().y());
    }
    if (this->getDirection()==UP){

        stop = nearestIntersection(pos())->getPosition().y()+50;
        startOfIntersection = QPointF( pos().x(), stop);
    }
    if (this->getDirection()==DOWN){
        stop = nearestIntersection(pos())->getPosition().y()-50;
        startOfIntersection = QPointF( pos().x(), stop);
    }

    return startOfIntersection;
}

void car::onLightChanged(bool greenForCars,QPointF interPos)
{
    if(this->getDirection() == RIGHT || this->getDirection() == LEFT){
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

    if(this->getDirection() == UP || this->getDirection() == DOWN){
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

