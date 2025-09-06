#include "car.h"
#include "qbrush.h"
#include "qdebug.h"
#include <QRandomGenerator>

#include <QPropertyAnimation>
#include <QEasingCurve>



car::car(Direction dir, const std::vector<intersection *> &intersections, QGraphicsItem *parent)
    :QObject(), MovingObject(), intersections(intersections), turning(false)
{
    setRect(-10, -10, 20, 20);
    setBrush(QBrush(Qt::red));
    setSpeed(3.0);
    setDirection(dir);

}

void car::move()
{
        //if (turning) return;
       QPointF posNow = pos();
       double minDist = 1e9;
       traffic_lights_controller* nearest_controller = nullptr;
       intersection* nearest_intersection = nullptr;

       // find nearest intersection
       for (auto* i : intersections){
           double dx = i->getPosition().x() - posNow.x();
           double dy = i->getPosition().y() - posNow.y();
           double dxy = std::sqrt(dx*dx + dy*dy);

           if (dxy < minDist && lastIntersection != i){

                   minDist = dxy;
                   nearest_intersection = i;



           }
       }
       if (nearest_intersection && nearest_intersection->hasLights()) {
               nearest_controller = nearest_intersection->getController();


               if (nearest_controller != currentController) {
                   if (currentController) {
                       disconnect(currentController, nullptr, this, nullptr);
                   }
                   currentController = nearest_controller;
                   connect(currentController, &traffic_lights_controller::lightChanged,
                           this, &car::onLightChanged);
                   stopAt = currentController->getPosition();
               }

              qDebug() <<"nearest int"<< nearest_intersection->getPosition();
              if(this->getDirection()==RIGHT)
                if (posNow.x() < nearest_intersection->getPosition().x()) if(minDist < 100) this->setSpeed(1);
              if(this->getDirection()==LEFT)
                if (posNow.x() > nearest_intersection->getPosition().x()) if(minDist < 100) this->setSpeed(1);
              if(this->getDirection()==UP)
                if (posNow.y() > nearest_intersection->getPosition().y()) if(minDist < 100) this->setSpeed(1);
              if(this->getDirection()==DOWN)
                if (posNow.y() < nearest_intersection->getPosition().y()) if(minDist < 100) this->setSpeed(1);

               //if (minDist < stop_distance && minDist > 10){
              qDebug() <<"x now"<< posNow.x();

              int stop;
              if (this->getDirection()==RIGHT) stop = nearest_intersection->getPosition().x()-50;
              if (this->getDirection()==LEFT) stop = nearest_intersection->getPosition().x()+50;
              if (this->getDirection()==UP) stop = nearest_intersection->getPosition().y()+50;
              if (this->getDirection()==DOWN) stop = nearest_intersection->getPosition().y()-50;


              qDebug() <<"stop"<<stop;


              if (this->getDirection()==RIGHT){
                  if(posNow.x() == stop){
                    qDebug() <<"here";
                   if (posNow.x() < nearest_intersection->getPosition().x()){
                       if( !currentController->getState()) {
                        setSpeed(0);  // zatrzymaj się tylko, gdy blisko i czerwone
                       }
                       else{
                           this->setSpeed(getDefaultSpeed());
                       }
                   }
                   else{
                       this->setSpeed(getDefaultSpeed());
                   }

               }




                            if (posNow.x() == stop + 30) {
                                rightOrStraight(lastIntersection);
                            }


                            if (posNow.x() == stop + 75) {
                                leftOrStraight(lastIntersection);
                            }


                  if(posNow.x() > stop+100) {
                      setSpeed(getDefaultSpeed());}
               }


              if (this->getDirection()==LEFT){
                  if (posNow.x() == stop){
                    qDebug() <<"here";
                   if (posNow.x() > nearest_intersection->getPosition().x()){
                       if( !currentController->getState()) {
                        setSpeed(0);  // zatrzymaj się tylko, gdy blisko i czerwone
                       }
                       else{
                           this->setSpeed(getDefaultSpeed());
                       }
                   }
                   else{
                       this->setSpeed(getDefaultSpeed());
                   }
                   //decideDirection();
               }
                          if (posNow.x() == stop - 30) {
                              rightOrStraight(nearest_intersection);
                          }

                          if (posNow.x() == stop - 75) {
                              leftOrStraight(nearest_intersection);
                          }



                  if(posNow.x() < stop-100) {
                      setSpeed(getDefaultSpeed());
                  }

                }

              if (this->getDirection()==UP){
                  if (posNow.y() == stop){
                    qDebug() <<"here";
                   if (posNow.y() > nearest_intersection->getPosition().y()){
                       if( currentController->getState()) {
                        setSpeed(0);  // zatrzymaj się tylko, gdy blisko i czerwone
                       }
                       else{
                           this->setSpeed(getDefaultSpeed());
                       }
                   }
                   else{
                       this->setSpeed(getDefaultSpeed());
                   }
                   //decideDirection();
               }

                          if (posNow.y() == stop - 30) {
                              rightOrStraight(nearest_intersection);
                          }

                          if (posNow.y() == stop - 75) {
                              leftOrStraight(nearest_intersection);
                          }


                  if(posNow.y() < stop-100){
                      setSpeed(getDefaultSpeed());
                    }
                }

              if (this->getDirection()==DOWN){
                  if (posNow.y() == stop){
                    qDebug() <<"here";
                   if (posNow.y() < nearest_intersection->getPosition().y()){
                       if( currentController->getState()) {
                        setSpeed(0);  // zatrzymaj się tylko, gdy blisko i czerwone
                       }
                       else{
                           this->setSpeed(getDefaultSpeed());
                       }
                   }
                   else{
                       this->setSpeed(getDefaultSpeed());
                   }
                   //decideDirection();
               }
                  int choice1 = QRandomGenerator::global()->bounded(2); // 0=prosto, 1=skręt
                  int choice2 = QRandomGenerator::global()->bounded(2); // 0=prawo, 1=lewo


                          if (posNow.y() == stop + 30) {
                              rightOrStraight(nearest_intersection);
                          }
                          if (posNow.y() == stop + 75) {
                              leftOrStraight(nearest_intersection);
                          }

                  if(posNow.y() > stop+100){
                      setSpeed(getDefaultSpeed());
                  }

                }




        }

        if (nearest_intersection && !nearest_intersection->hasLights()) {
           // qDebug() << "minDist =" << minDist << "stop_distance =" << stop_distance;
            if (minDist < stop_distance) {
                //decideDirection();
                qDebug() << "bez swiatel" ;
             }
        }


    MovingObject::move();
}

void car::decideDirection()
{
    int choice = 2;//QRandomGenerator::global()->bounded(3); // 0=prosto, 1=lewo, 2=prawo

    if (this->getDirection() == Direction::RIGHT) {
        if (choice == 1) {
            this->setDirection(UP);      // skręt w lewo (na razie instant)
        }
        else if (choice == 2) {
         this->setPos(pos().x()+20, pos().y());
         this->setDirection(DOWN);
        }
    }
    else if (this->getDirection() == Direction::LEFT) {
        if (choice == 1) this->setDirection(DOWN);
        else if (choice == 2) this->setDirection(UP);
    }
    else if (this->getDirection() == Direction::UP) {
        if (choice == 1) this->setDirection(LEFT);
        else if (choice == 2) this->setDirection(RIGHT);
    }
    else if (this->getDirection() == Direction::DOWN) {
        if (choice == 1) this->setDirection(RIGHT);
        else if (choice == 2) this->setDirection(LEFT);
    }
}


void car::turnRight()
{
    int i = 0;

    for (i; i< 25; i++){
        setPos(pos().x() + 1, pos().y());
    }


}

void car::leftOrStraight(intersection* i)
{

    int choice = QRandomGenerator::global()->bounded(2); // 0=prosto, 1=lewo
    if (this->getDirection() == RIGHT){
        if (choice ==1) this->setDirection(UP);
        turning = true;
        lastIntersection = i;
    }

    if (this->getDirection() == LEFT){
        if (choice ==1) this->setDirection(DOWN);
        turning = true;
        lastIntersection = i;
    }

    if (this->getDirection() == UP){
        if (choice ==1) this->setDirection(LEFT);
        turning = true;
        lastIntersection = i;
    }

    if (this->getDirection() == DOWN){
        if (choice ==1) this->setDirection(RIGHT);
        turning = true;
        lastIntersection = i;

    }

}

void car::rightOrStraight(intersection* i)
{

    int choice = QRandomGenerator::global()->bounded(2); // 0=prosto, 1=prawo
    if (this->getDirection() == RIGHT){
        if (choice ==1) this->setDirection(DOWN);
        turning = true;
    }

    if (this->getDirection() == LEFT){
        if (choice ==1) this->setDirection(UP);
        turning = true;
    }

    if (this->getDirection() == UP){
        if (choice ==1) this->setDirection(RIGHT);
        turning = true;
    }

    if (this->getDirection() == DOWN){
        if (choice ==1) this->setDirection(LEFT);
        turning = true;
    }
    lastIntersection = i;

}

void car::onLightChanged(bool greenForCars,QPointF interPos)
{
    if(this->getDirection() == RIGHT || this->getDirection() == LEFT){
        if (qFuzzyCompare(stopAt.x(), interPos.x()) &&
                qFuzzyCompare(stopAt.y(), interPos.y()))
            {
                if (greenForCars) {
                    qDebug() << "🚗 Ruszam, bo zielone!";
                    QTimer::singleShot(2000, this, [this]() {
                        setSpeed(getDefaultSpeed());
                        if (currentController) {
                                        disconnect(currentController, nullptr, this, nullptr);
                                        currentController = nullptr;
                                    }
                        currentController = nullptr; // już przejechał
                    });

                } else {
                    qDebug() << "🚗 Stoję, czerwone.";
                }
            }
    }

    if(this->getDirection() == UP || this->getDirection() == DOWN){
        if (qFuzzyCompare(stopAt.x(), interPos.x()) &&
                qFuzzyCompare(stopAt.y(), interPos.y()))
            {
                if (!greenForCars) {
                    qDebug() << "🚗 Ruszam, bo zielone!";
                    QTimer::singleShot(2000, this, [this]() {
                        setSpeed(getDefaultSpeed());
                        if (currentController) {
                                        disconnect(currentController, nullptr, this, nullptr);
                                        currentController = nullptr;
                                    }
                        currentController = nullptr; // już przejechał
                    });
                } else {
                    qDebug() << "🚗 Stoję, czerwone.";
                }
            }
    }

}

