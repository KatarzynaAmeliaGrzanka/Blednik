#ifndef TRAFFIC_LIGHTS_H
#define TRAFFIC_LIGHTS_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

class traffic_lights : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit traffic_lights(QGraphicsItem* parent = nullptr);
    bool isGreen() const {return m_isGreen; };
    void setState(bool green);

private:
    bool m_isGreen;
};

#endif // TRAFFIC_LIGHTS_H
