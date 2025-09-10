#ifndef TRAFFIC_LIGHTS_CONTROLLER_H
#define TRAFFIC_LIGHTS_CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <vector>
#include "traffic_lights.h"


/**
 * @brief The traffic_lights_controller class
 * Klasa kontrolera świateł, która implementuje światła na całym skrzyżowaniu, tzn. 4 pojedyncze światła.
 * Posiada sygnał zmiany światła.
 *
 */
class traffic_lights_controller : public QObject
{
    Q_OBJECT
public:
    /**
    * @brief traffic_lights_controller Konstruktor.
    * @param parent
    */
   explicit traffic_lights_controller(QObject* parent = nullptr);
    /**
    * @brief addIntersection Metoda dodająca cztery światła storzące skrzyżowanie do kontrolera.
    * @param north światło 1
    * @param south światło 2
    * @param east światło 3
    * @param west światło 4
    */
   void addIntersection(traffic_lights* north, traffic_lights* south,traffic_lights* east, traffic_lights* west);
   /**
    * @brief getPosition Metoda zwracająca pozycję kontrolera.
    * @return Współrzędne.
    */
   QPointF getPosition();
   /**
    * @brief setPosition Metoda ustawiająca położenie kontrolera.
    * @param x
    * @param y
    */
   void setPosition(qreal x, qreal y);
   /**
    * @brief getState Metoda zwracająca aktualny stan kontrolera.
    * @return
    */
   bool getState(){return m_state;} // stan dla całego skrzyzowania

signals:
   /**
    * @brief lightChanged sygnał zmiany światłą
    * @param carGreen
    * @param position
    */
   void lightChanged(bool carGreen, QPointF position);

public slots:
   /**
     * @brief toggle Funkcja zmieniająca światła w kontrolerze (czyli na całym skrzyżowaniu).
     */
    void toggle();

private:
    struct m_Intesection{
        traffic_lights* north;
        traffic_lights* south;
        traffic_lights* east;
        traffic_lights* west;
    };
    /**
     * @brief intersections Wektor skrzyżowań
     */
    std::vector<m_Intesection> m_intersections;
    /**
     * @brief timer Timer do wysyłania sygnału.
     */
    QTimer m_timer;
    /**
     * @brief state stan kontrolera.
     */
    bool m_state = true;
    /**
     * @brief position Położenie kontrolera.
     */
    QPointF m_position;
};

#endif // TRAFFIC_LIGHTS_CONTROLLER_H
