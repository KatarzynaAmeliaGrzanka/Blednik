#ifndef INTERSECTION_H
#define INTERSECTION_H


#include "qpoint.h"
#include "traffic_lights_controller.h"

/**
 * @brief The intersection class
 *
 * Klasa implemetująca skrzyżowanie na mapie zawierająca pozycję, aktualny stan (czy jest na nim samochód) oraz możliwość połączenia z kontrolerem świateł, jeśli są na tym skrzyżowaniu.
 *
 */

class intersection
{
public:
    /**
     * @brief intersection Konstruktor
     * @param pos Pozycja ma mapie skrzyżowania
     * @param controller Kontroler świateł na skrzyżowaniu, może być nullptr.
     */
    intersection(QPointF pos, traffic_lights_controller* controller = nullptr)
        : m_position(pos), m_controller(controller){}

    /**
     * @brief getPosition Metoda do zwrazania pkoordynatów skrzyżowania.
     * @return
     */
    QPointF getPosition() const { return m_position; }
    /**
     * @brief getController Metoda do zwracania kontrolera na skrzyżowaniu.
     * @return wskaźnik do kontrolera.
     */
    traffic_lights_controller* getController() const {return m_controller;}
    /**
     * @brief hasLights Metoda do sprawdzania, czy na skrzyżowaniu są światła.
     * @return true - są światła, false - nie ma świateł
     */
    bool hasLights() const {return m_controller != nullptr; }
    /**
     * @brief addController Metoda do dodawania kontrolera świateł do skrzyżowania.
     * @param tctr  wskaźnik do kontrolera.
     */
    void addController(traffic_lights_controller* tctr) {m_controller = tctr;}
    /**
     * @brief isOccupied Metoda do spawdzania, czy aktualnie jakiś samochód jest na skrzyżowaniu.
     * @return
     */
    bool isOccupied() const {return m_occupied; }
    /**
     * @brief setOccupied Metoda do zapisania informacji, że samochód jest na skrzyżowaniu.
     */
    void setOccupied() {m_occupied = true;};
    /**
     * @brief setEmpty etoda do zapisania informacji, że samochód opuścił skrzyżowanie.
     */
    void setEmpty() {m_occupied = false;};

private:
    /**
     * @brief position Pozycja skrzyżowania na mapie.
     */
    QPointF m_position;
    /**
     * @brief controller Kontroler świateł na skrzyżowaniu.
     */
    traffic_lights_controller* m_controller;
    /**
     * @brief occupied true - na skrzyżowaniu jest aktualnie samochód, false - na skrzyżowaniu nie ma aktualnie samochodu.
     */
    bool m_occupied = false;
};

#endif // INTERSECTION_H
