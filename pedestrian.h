#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "intersection.h"
#include "movingobject.h"
#include "pedestrian_crossing.h"

/**
 * @brief The pedestrian class
 * Klasa dziedzicząca po MovingObject zawierająca implementację pieszego, który porusza się po mapie.
 */
class pedestrian : public QObject, public MovingObject {
    Q_OBJECT
    /**
     * @brief The PedestrianState enum
     * Struktura enum przechowująca stany, w których może byc pieszy.
     */
    enum PedestrianState {
        WALKING,
        APPROACHING,
        WAITING,
        TURNING,
        CROSSING,
        DECIDING,
        TURN_RIGHT,
        TURN_LEFT,
        APPROACHING_CROSSING
    };
public:
    /**
     * @brief pedestrian Konstruktor.
     * @param dir Kierunek poruszania.
     * @param intersections wektror skrzyżowań.
     * @param crossings Wektor przejść dla pieszych.
     * @param car_start_points Wektor współrzędnych punktów, z których mogą ruszać samochody.
     * @param parent
     */
    pedestrian(Direction::direction dir, const std::vector<intersection*>& intersections, const std::vector<pedestrian_crossing*>& crossings, std::vector<QPointF> car_start_points,
               QGraphicsItem* parent = nullptr);
    /**
     * @brief move Metoda (polimorfizm) implementująca ruch pieszego, bazująca na zmianach stanów.
     */
    void move() override;
    /**
     * @brief goAhead Metoda implementująca prosty rych do przodu i zachowanie na końcach mapy.
     */
    void goAhead();
    /**
     * @brief nearestIntersection Metoda zwracająca najbliższe skrzyżowanie.
     * @param pos Współrzędne punktu.
     * @return Wskaźnik do skrzyżowania,
     */
    intersection * nearestIntersection(QPointF pos);
    /**
     * @brief nearestCrossing  Metoda zwracająca najbliższe przejscie dla pieszych.
     * @param pos Pozycja
     * @return Wskaźnik do przejścia dla pieszych.
     */
    pedestrian_crossing* nearestCrossing(QPointF pos);
    /**
     * @brief distance Metoda do obliczania odległości między dwoma punktami.
     * @param a QPointF
     * @param b QPointF
     * @return Zmiennoprzecinkowa wartość odległości między a i b.
     */
    qreal distance(QPointF a, QPointF b);
    /**
     * @brief getTurnPoint Metoda do zwracanie punktu zmiany kierunku przy skrzyżowaniu w zależności z której strony nadchodzi pieszy.
     * @return wartość jednej współżędnej punktu.
     */
    int getTurnPoint();

private:
    /**
     * @brief state aktualny stan pieszego.
     */
    PedestrianState m_state = WALKING;
    /**
     * @brief intersections wektor skrzyżowań.
     */
    std::vector<intersection*> m_intersections;
    /**
     * @brief crossings Wektor przejść dla pieszych.
     */
    std::vector<pedestrian_crossing*> m_crossings;
    /**
     * @brief lastIntersection Ostatnie skrzyżowanie, na którym był pieszy.
     */
    intersection* m_lastIntersection = nullptr;
    /**
     * @brief lastCrossing Ostatnie przejście, na którym był pieszy.
     */
    pedestrian_crossing* m_lastCrossing = nullptr;
    /**
     * @brief car_start_points Punkty, z którch starują smaochody w symulacji.
     */
    std::vector<QPointF> m_car_start_points;

};

#endif // PEDESTRIAN_H
