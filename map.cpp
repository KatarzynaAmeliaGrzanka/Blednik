#include "map.h"



map::map(int width, int height)
{
    m_map_width = width;
    m_map_height = height;
}

void map::setVerticalRoad(int x)
{
    m_vertical_roads.push_back(x);
    m_Roads.push_back(QRectF(x-m_road_width/2, 0, m_road_width, m_map_height));
}

void map::setHorizontalRoad(int y)
{
    m_horizontal_roads.push_back(y);
    m_Roads.push_back(QRectF(0, y-m_road_width/2, m_map_width, m_road_width));

}

void map::setRoadWidth(int w)
{
    m_road_width = w;
}

std::vector<QRectF> map::getRoads()
{
    return m_Roads;
}

std::vector<QPointF> map::getCrossroads()
{
    std::vector<QPointF> crossroads;
    for(auto x : m_vertical_roads) {
        for (auto y : m_horizontal_roads){
            crossroads.push_back(QPointF(x,y));
        }
    }
    return crossroads;
}

std::vector<int> map::getHorizontalRoads()
{
    return m_horizontal_roads;
}

std::vector<int> map::getVerticalRoads()
{
    return m_vertical_roads;
}

int map::getMapWidth(){
    return m_map_width;
}

int map::getMapHeight(){
    return m_map_height;
}


