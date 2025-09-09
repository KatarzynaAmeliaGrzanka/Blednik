#ifndef TRAFFIC_LIGHTS_H
#define TRAFFIC_LIGHTS_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

/**
 * @brief The traffic_lights class
 * Klasa implementująca pojedyncze światło, które może być czerwone albo zielone.
 */

class traffic_lights : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    /**
     * @brief traffic_lights Konstruktor
     * @param parent
     */
    explicit traffic_lights(QGraphicsItem* parent = nullptr);
    /**
     * @brief isGreen Metoda zwracająca informację, czy światło jest zielone.
     * @return
     */
    bool isGreen() const {return m_isGreen; };
    /**
     * @brief setState Metoda zwracająca stan (kolor).
     * @param green
     */
    void setState(bool green);
    /**
     * @brief getState Metoda ustawiająca kolor światła.
     * @return
     */
    bool getState();

private:
    /**
     * @brief m_isGreen Kolor światła przedstawiony jako true (zielone) i false (czerwone).
     */
    bool m_isGreen;
};

#endif // TRAFFIC_LIGHTS_H
