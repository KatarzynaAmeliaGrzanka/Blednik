#include "car.h"
#include "qbrush.h"
#include "qdebug.h"





car::car(const std::vector<traffic_lights_controller *> &lights, QGraphicsItem *parent)
    :MovingObject()
{
    setRect(-10, -5, 20, 10);
    setBrush(QBrush(Qt::red));
    setSpeed(3.0);

    for (auto* ctrl : lights) {
           connect(ctrl, &traffic_lights_controller::lightChanged,
                   this, &car::onLightChanged);
       }
}

void car::move()
{
    QPointF posNow = pos();
       double minDist = 1e9;
       traffic_lights_controller* nearest = nullptr;

       // znajdź najbliższe skrzyżowanie przed samochodem
       for (auto* c : controllers) {
           QPointF inter = c->getPosition();
           double dx = inter.x() - posNow.x();
           if (dx >= 0 && dx < minDist) { // tylko przed samochodem
               minDist = dx;
               nearest = c;
           }
       }

       if (nearest) {
           currentController = nearest;
           QPointF inter = nearest->getPosition();

           if (abs(inter.x() - posNow.x()) < 50){
           // zatrzymaj się jeśli blisko i czerwone
           if (minDist < stop_distance && !nearest->getState()) {
               setSpeed(0);
               stopAt = inter;
           }
       }
       }

       MovingObject::move(); // normalny ruch (x += speed)
    if (currentController) {
            QPointF inter = currentController->getPosition();
            double dx = inter.x() - pos().x();

            // zatrzymaj się, gdy blisko skrzyżowania i czerwone
            if (dx < 30 && dx > 0 && !currentController->getState()) {
                setSpeed(0);
                stopAt = inter;
            }
        }



    MovingObject::move();

}

void car::onLightChanged(bool greenForCars,QPointF interPos)
{
    if (qFuzzyCompare(stopAt.x(), interPos.x()) &&
            qFuzzyCompare(stopAt.y(), interPos.y()))
        {
            if (greenForCars) {
                qDebug() << "🚗 Ruszam, bo zielone!";
                setSpeed(getDefaultSpeed());
                currentController = nullptr; // już przejechał
            } else {
                qDebug() << "🚗 Stoję, czerwone.";
            }
        }

}
