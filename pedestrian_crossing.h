#ifndef PEDESTRIAN_CROSSING_H
#define PEDESTRIAN_CROSSING_H
#include <QObject>
#include <QGraphicsRectItem>



#include "qpoint.h"

/**
 * @brief The pedestrian_crossing class
 * Klasa implementująca przejście dla pieszych na mapie.
 */

class pedestrian_crossing:   public QGraphicsRectItem{


public:
    /**
     * @brief pedestrian_crossing Konstruktor.
     * @param position Współrzędne przejścia.
     */
    pedestrian_crossing(QPointF position);
    /**
     * @brief setOccupied Metoda zapisująca, że na pasach jest pieszy.
     */
    void setOccupied() { Occupied = true; }
    /**
     * @brief setEmpty Metoda zapisująca, że pieszy zszedł z pasów.
     */
    void setEmpty() { Occupied = false; }
    /**
     * @brief isOccupied Metoda wzracająca informację, czy na pasach jest pieszy.
     * @return bool
     */
    bool isOccupied() { return Occupied;};
    /**
     * @brief getPosition Metoda zwracająca współrzędne przejścia.
     * @return QPointF
     */
    QPointF getPosition() { return position;}
    /**
     * @brief getStop1 Metoda zwracająca współrzędne punktu wejścia na przejście po lewej stronie przejścia.
     * @return
     */
    QPointF getStop1() {return stop1; };
    /**
     * @brief getStop2 Metoda zwracająca współrzędne punktu wejścia na przejście po prawej stronie przejścia.
     * @return
     */
    QPointF getStop2() {return stop2; };

private:
    /**
     * @brief position Wpółrzędne przejścia na mapie.
     */
    QPointF position;
    /**
     * @brief Occupied True - pieszy na pasach, false - nie ma pieszego na pasach.
     */
    bool Occupied = false;
    /**
     * @brief stop1 współrzędne punktu wejścia na przejście po lewej stronie przejścia.
     */
    QPointF stop1;
    /**
     * @brief stop2 współrzędne punktu wejścia na przejście po prawej stronie przejścia
     */
    QPointF stop2;
};

#endif // PEDESTRIAN_CROSSING_H
