#include "map.h"



map::map(int width, int height)
{
    map_width = width;
    map_height = height;
}

void map::setVerticalRoad(int x)
{
    vertical_roads.push_back(x);
    Roads.push_back(QRectF(x-road_width/2, 0, road_width, map_height));
}

void map::setHorizontalRoad(int y)
{
    horizontal_roads.push_back(y);
    Roads.push_back(QRectF(0, y-road_width/2, map_width, road_width));

}

void map::setRoadWidth(int w)
{
    road_width = w;
}

std::vector<QRectF> map::getRoads()
{
    return Roads;
}

std::vector<QPointF> map::getCrossroads()
{
    std::vector<QPointF> crossroads;
    for(auto x : vertical_roads) {
        for (auto y : horizontal_roads){
            crossroads.push_back(QPointF(x,y));
        }
    }
    return crossroads;
}

std::vector<int> map::getHorizontalRoads()
{
    return horizontal_roads;
}

std::vector<int> map::getVerticalRoads()
{
    return vertical_roads;
}

int map::getMapWidth(){
    return map_width;
}

int map::getMapHeight(){
    return map_height;
}


