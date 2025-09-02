#ifndef MAP_H
#define MAP_H

#include <QGraphicsRectItem>

class map
{
public:
    map(int width, int height);

    void setVerticalRoad(int x);
    void setHorizontalRoad(int y);
    void setRoadWidth(int w);
    std::vector<QRectF> getRoads();
    std::vector<QPointF> getCrossroads();
    std::vector<int> getHorizontalRoads();
    std::vector<int> getVerticalRoads();

    int getMapWidth();
    int getMapHeight();

private:
    int map_width;
    int map_height;
    int road_width;
    std::vector<QRectF> Roads;
    std::vector<int> horizontal_roads;
    std::vector<int> vertical_roads;

};

#endif // MAP_H
