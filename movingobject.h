#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <QGraphicsRectItem>
#include <QObject>
#include "Direction.h"
/**
 * @brief The MovingObject class
 * Klasa abstrakcyjna implementująca zachowanie ruszającego się przedmiotu na mapie.
 */

class MovingObject :  public QGraphicsRectItem {

public:
    /**
     * @brief MovingObject Konstruktor
     */
    MovingObject();
    /**
     * @brief setSpeed Metoda ustawiająca prędkość przedmiotu.
     * @param s wartość prędkości qreal.
     */
    void setSpeed(qreal s);
    /**
     * @brief getDefaultSpeed Metoda zwracająca domyślną prędkość przedmiotu.
     * @return
     */
    qreal getDefaultSpeed() {return m_default_speed;}
    /**
     * @brief setDirection Metoda ustawiająca kierunek, w którym porusza się przedmiot.
     * @param d kierunek z klasy Direction.
     */
    void setDirection(Direction::direction d) {m_direction = d;};
    /**
     * @brief getDirection Metoda zwracająca kierunek, w którym porusza się przedmiot.
     * @return
     */
    Direction::direction getDirection() const {return m_direction; }
    /**
     * @brief getSpeed Metoda zwracająca aktualną prędkość przedmiotu.
     * @return
     */
    qreal getSpeed() const {return m_speed;}
    /**
     * @brief move wirtualna metoda do implementacji ruchu przedmiotu.
     */
    virtual void move() = 0;

private:
    /**
     * @brief speed Zmiennoprzecinkowa wartość prędkości przedmiotu.
     */
    qreal m_speed;
    /**
     * @brief default_speed Zmiennoprzecinkowa wartość domyślnej prędkości przedmiotu.
     */
    qreal m_default_speed = 3;
    /**
     * @brief direction kierunek poruszania się z klasy Direction.
     */
    Direction::direction m_direction = Direction::RIGHT;
};

#endif // MOVINGOBJECT_H
