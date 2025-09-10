#ifndef MAP_H
#define MAP_H

#include <QGraphicsRectItem>

/**
 * @brief The map class
 * Klasa implementująca mapę symulacji. Jest odpowiedzialna sa tworzenie dróg i skrzyżowań.
 */
class map
{
public:
    /**
     * @brief map Konstruktor
     * @param width Szerokość mapy
     * @param height Wysokość mapy
     */
    map(int width, int height);
    /**
     * @brief setVerticalRoad Metoda tworząca pionową drogę.
     * @param x Współrzędna x drogi.
     */
    void setVerticalRoad(int x);
    /**
     * @brief setHorizontalRoad Metoda tworząca poziomą drogę.
     * @param y Współrzędna y drogi.
     */
    void setHorizontalRoad(int y);
    /**
     * @brief setRoadWidth Metoda to ustawienia domyślnej szerokości drogi.
     * @param w
     */
    void setRoadWidth(int w);
    /**
     * @brief getRoads Metoda zwracająca drogi na mapie.
     * @return wektor współrzędnych dróg na mapie.
     */
    std::vector<QRectF> getRoads();
    /**
     * @brief getCrossroads Metoda zwracająca skrzyżowania na mapie.
     * @return wektor współrzędnych skrzyżowań na mapie.
     */
    std::vector<QPointF> getCrossroads();
    /**
     * @brief getHorizontalRoads Metoda zwracająca drogi pionowe na mapie.
     * @return wektor współrzędnych dróg pionowych na mapie.
     */
    std::vector<int> getHorizontalRoads();
    /**
     * @brief getVerticalRoads Metoda zwracająca drogi poziome na mapie.
     * @return wektor współrzędnych dróg poziomych na mapie.
     */
    std::vector<int> getVerticalRoads();
    /**
     * @brief getMapWidth Metoda zwracająca szerokość mapy.
     * @return integer
     */
    int getMapWidth();
    /**
     * @brief getMapHeight Metoda zwracająca Wysokość mapy.
     * @return
     */
    int getMapHeight();

private:
    /**
     * @brief map_width Szerokość mapy
     */
    int m_map_width;
    /**
     * @brief map_height Wysokość mapy
     */
    int m_map_height;
    /**
     * @brief road_width Szerokość drogi
     */
    int m_road_width;
    /**
     * @brief Roads Wektor współrzędnuch dróg
     */
    std::vector<QRectF> m_Roads;
    /**
     * @brief horizontal_roads Wektor współrzędnuch dróg poziomych.
     */
    std::vector<int> m_horizontal_roads;
    /**
     * @brief vertical_roads Wektor współrzędnuch dróg pionowych.
     */
    std::vector<int> m_vertical_roads;

};

#endif // MAP_H
