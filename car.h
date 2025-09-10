#ifndef CAR_H
#define CAR_H
#include "intersection.h"
#include "movingobject.h"
#include "pedestrian_crossing.h"
#include "traffic_lights_controller.h"

/**
 *  Klasa samochodu.
 *
 *  Klasa samochodu dziedziczy po MovingObject.
 *  Klasa ta reprezentuje samochód poruszający się w symulacji.
 *  Implementuje ruch samochodu, który reaguje na skrzyżowania,
 *  pieszych oraz sygnalizację świetlną.
 *
 */

class car : public QObject, public MovingObject {
        Q_OBJECT

public:

    /**
     * @brief The CarState enum
     * Samochód korzysta ze struktury enum, która przechowuje stany,
     * w których może się znajdować samochów.
     */
    enum CarState {
        DRIVING,
        APPROACHING,
        WAITING,
        CROSSING,
        DECIDING,
        TURN_RIGHT,
        TURN_LEFT,
        WAITING_AT_CROSSING,
        WAITING_TO_CROSS

    };
    /**
     * @brief car konstruktor samochodu.
     * @param dir wartość z klasy Direction, która przechowuje kierunek poruszania się.
     * @param intersections wektor przechowujący wszystkies skrzyżowania.
     * @param crossings wektro przechowujący wszystkie przejścia dla pieszych.
     * @param parent
     */
    car(Direction::direction dir, const std::vector<intersection*>& intersections, const std::vector<pedestrian_crossing*>& crossings,
        QGraphicsItem* parent = nullptr);
    /**
     * @brief move metoda nadpisana implementująca ruch samochodu.
     */
    void move() override;
    /**
     * @brief addControllers metoda ustawia wartość przechowującą kontroleru świateł
     * @param c wektor z kontrolerami świateł ulicznych na mapie.
     */
    void addControllers(std::vector<traffic_lights_controller*> c){m_controllers = c;};
    /**
     * @brief nearestIntersection metoda zwracająca najbliższe skrzyżowanie
     * @param pos QPointF z pozycją, dla której będzie sprawdzać
     * @return wskaźnik do obiektu klasy intersection (skrzyżowanie)
     */
    intersection* nearestIntersection(QPointF pos);
    /**
     * @brief nearestCrossing metoda zwracająca najbliższe przejście dla pieszych
     * @param pospos QPointF z pozycją, dla której będzie sprawdzać
     * @return  wskaźnik do obiektu klasy pedestrian_crossing
     */
    pedestrian_crossing* nearestCrossing(QPointF pos);
    /**
     * @brief goAhead metoda do prostego ruchu samochodu na przód.
     */
    void goAhead();
    /**
     * @brief getStartOfIntersection metoda zwracająca pozycję, gdzie zaczyna się skrzyżowanie w zależności z której strony nadjeżdża samochód.
     * @param dir wartość z klasy Direction, która przechowuje kierunek poruszania się.
     * @return
     */
    QPointF getStartOfIntersection(Direction::direction dir);


public slots:
    /**
    * @brief onLightChanged funkcja reagująca na sygnał zmiany świateł wysyłany przez kontroler
    * @param greenForCars wartość bool informująca czy jest zielone
    * @param interPos pozycja na mapie
    */
   void onLightChanged(bool greenForCars,QPointF interPos);

private:
   /**
    * @brief stopAt pozycja QPointF gdzie samochód ma się zatrzymać przed skrzyżowaniem.
    */
   QPointF m_stopAt;
   /**
     * @brief currentController wskaźnik do aktualnego kontrolera światłę, na który reaguje samochód
     */
    traffic_lights_controller* m_currentController = nullptr;
    /**
     * @brief controllers wektor wszystkich kontrolerów świateł na mapie.
     */
    std::vector<traffic_lights_controller*> m_controllers;
    /**
     * @brief crossings wektor wszystkich przejść dla pieszych.
     */
    std::vector<pedestrian_crossing*> m_crossings;
    /**
     * @brief intersections wektor wszystkich skrzyżowań na mapie.
     */
    std::vector<intersection*> m_intersections;
    /**
     * @brief lastIntersection zapamiętane ostatnie skrzyżowanie, na którym był samochód.
     */
    intersection* m_lastIntersection = nullptr;
    /**
     * @brief state aktualny stan samochodu (np. skręca, czeka itp.)
     */
    CarState m_state = DRIVING;
    /**
     * @brief startOfIntersection początek skrzyżowanie przed samochodem.
     */
    QPointF m_startOfIntersection;
};

#endif // CAR_H
