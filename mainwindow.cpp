#include "mainwindow.h"
#include <QGraphicsView>
#include "car.h"
#include "map.h"
#include "pedestrian.h"
#include "pedestrian_crossing.h"
#include "traffic_lights.h"
#include "traffic_lights_controller.h"
#include <QDebug>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>


MainWindow::MainWindow(int nbOfCars, int nbOfPedestrians,  QWidget *parent)
    : QMainWindow(parent)
    , scene(new QGraphicsScene(this))
{

    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);

    int map_dim = 900;
    int road_width = 80;
    map map(900, 900);
    std::vector<QPointF> start_points_cars;
    std::vector<QPointF> start_points_pedestrians;


    std::vector<traffic_lights_controller*> lights_controllers;
    std::vector<intersection*> intersections_on_map;
    std::vector<car*> cars;
    std::vector<pedestrian*> pedestrians;

    resize(map.getMapWidth(),map.getMapHeight());
    scene->setSceneRect(0,0,map.getMapWidth(),map.getMapHeight());

    map.setRoadWidth(road_width);
    map.setHorizontalRoad(map_dim/3);
    map.setHorizontalRoad(map_dim*2/3);
    map.setVerticalRoad(map_dim/4);
    map.setVerticalRoad(map_dim/2);
    map.setVerticalRoad(map_dim*3/4);

    pedestrian_crossing* crossing1 = new pedestrian_crossing(QPointF((map_dim/4 - road_width/2) , map_dim/2));
    scene->addItem(crossing1);

    pedestrian_crossing* crossing2 = new pedestrian_crossing(QPointF((map_dim/2) - road_width/2 , map_dim/2));
    scene->addItem(crossing2);

    pedestrian_crossing* crossing3 = new pedestrian_crossing(QPointF((map_dim*3/4) - road_width/2 , map_dim/2));
    scene->addItem(crossing3);

    std::vector<pedestrian_crossing*> crossings;
    crossings.push_back(crossing1);
    crossings.push_back(crossing2);
    crossings.push_back(crossing3);

    for (auto rect : map.getRoads()){
        QGraphicsRectItem* road = scene->addRect(rect, QPen(Qt::NoPen), QBrush(Qt::darkBlue));
        road->setZValue(-1);
    }

    for (auto road : map.getHorizontalRoads()) {
        for (int x=0; x < map.getMapWidth(); x+= 40){
            scene->addRect(x, road, 20, 3, QPen(Qt::NoPen), QBrush(Qt::white));
        }
        start_points_cars.push_back(QPointF(5 , road + 20));
        start_points_pedestrians.push_back(QPointF(5 , road + 60));
    }

    for (auto road : map.getVerticalRoads()) {
        for (int y=0; y < map.getMapHeight(); y+= 40){
            scene->addRect(road, y, 3, 20, QPen(Qt::NoPen), QBrush(Qt::white));
            scene->addEllipse(road - 25, 5, 10, 10, QPen(Qt::red), QBrush(Qt::red));

        }
        start_points_cars.push_back(QPointF(road - 25, 5));
        start_points_pedestrians.push_back(QPointF(road - 50, 5));

    }

    int counter = 0;
    for (auto point : map.getCrossroads()) {
        intersection* curr_intersection = new intersection(point);
        if (counter % 3 != 0){ // światła na 2/3 skrzyżowań
            traffic_lights* light1 = new traffic_lights();
            traffic_lights* light2 = new traffic_lights();
            traffic_lights* light3 = new traffic_lights();
            traffic_lights* light4 = new traffic_lights();

            light1->setPos(point.x() + 30, point.y()-50);  scene->addItem(light1);
            light2->setPos(point.x() + 30, point.y()+30);  scene->addItem(light2);
            light3->setPos(point.x() - 50, point.y()-50);  scene->addItem(light3);
            light4->setPos(point.x() - 50, point.y()+30);  scene->addItem(light4);

            auto controller = new traffic_lights_controller(this);
            controller->addIntersection(light1, light4, light2, light3); // pion
            lights_controllers.push_back(controller);
            controller->setPosition(point.x()-5, point.y()-5);

            curr_intersection->addController(controller);
        }
        intersections_on_map.push_back(curr_intersection);
        counter++;
    }



    for (int i = 0; i < nbOfCars && i < start_points_cars.size(); i++) {
        Direction::direction dir;

        if (i < 2) {
            dir = Direction::RIGHT;
        } else {
            dir = Direction::DOWN;
        }

        car* newCar = new car(dir, intersections_on_map, crossings);
        newCar->setPos(start_points_cars[i]);
        scene->addItem(newCar);
        newCar->addControllers(lights_controllers);
        cars.push_back(newCar);
    }


    for (int i = 0; i < nbOfPedestrians && i < start_points_pedestrians.size(); i++) {
        Direction::direction  dir;

        if (i < 2) {
            dir = Direction::RIGHT;
        } else {
            dir = Direction::DOWN;
        }

        pedestrian* newPedestrian = new pedestrian(dir, intersections_on_map, crossings, start_points_cars);
        newPedestrian->setPos(start_points_pedestrians[i]);
        scene->addItem(newPedestrian);
        pedestrians.push_back(newPedestrian);

    }


    QTimer* anim = new QTimer(this);
    connect(anim, &QTimer::timeout, this, [=](){
        for (auto c : cars) {
            c->move();
        }
        for (auto p : pedestrians) {
            p->move();
        }
    });
    anim->start(30);
}

MainWindow::~MainWindow()
{
}

