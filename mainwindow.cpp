#include "mainwindow.h"
#include <QGraphicsView>
#include "car.h"
#include "map.h"
#include "traffic_lights.h"
#include "traffic_lights_controller.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , scene(new QGraphicsScene(this))
{

    // Widok
    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);

    map map(1200, 1200);

    resize(map.getMapWidth(),map.getMapHeight());
    scene->setSceneRect(0,0,map.getMapWidth(),map.getMapHeight());

    map.setRoadWidth(80);
    map.setHorizontalRoad(300);
    map.setHorizontalRoad(700);
    map.setVerticalRoad(200);
    map.setVerticalRoad(600);
    map.setVerticalRoad(1000);

    //qDebug() << "Liczba dróg:" << map.getRoads().size();

    for (auto rect : map.getRoads()){
        //qDebug() << "Dodaję drogę:" << rect;
        QGraphicsRectItem* road = scene->addRect(rect, QPen(Qt::NoPen), QBrush(Qt::darkBlue));
        road->setZValue(-1);
    }

    for (auto point : map.getCrossroads()) {
        scene->addEllipse(point.x()-5, point.y()-5, 10, 10, QPen(Qt::red), QBrush(Qt::red));
    }


    for (auto road : map.getHorizontalRoads()) {
        //qDebug() << "Droga" << road;
        for (int x=0; x < map.getMapWidth(); x+= 40){
            scene->addRect(x, road, 20, 3, QPen(Qt::NoPen), QBrush(Qt::white));
        }
    }

    for (auto road : map.getVerticalRoads()) {
        //qDebug() << "Droga" << road;
        for (int y=0; y < map.getMapHeight(); y+= 40){
            scene->addRect(road, y, 3, 20, QPen(Qt::NoPen), QBrush(Qt::white));
        }
    }


    /*for (auto point : map.getCrossroads()) {
        traffic_lights* light = new traffic_lights();
        light->setPos(point.x() + 20, point.y()-20);  // np. na skrzyżowaniu
        scene->addItem(light);
        light->setPos(point.x() - 20, point.y()+20);  // np. na skrzyżowaniu
        scene->addItem(light);
    }*/

    std::vector<traffic_lights_controller*> lights_controllers;


    int counter = 0;
    for (auto point : map.getCrossroads()) {
        if (counter % 3 != 0){
        traffic_lights* light1 = new traffic_lights();
        traffic_lights* light2 = new traffic_lights();
        traffic_lights* light3 = new traffic_lights();
        traffic_lights* light4 = new traffic_lights();

        light1->setPos(point.x() + 50, point.y()-70);  scene->addItem(light1);
        light2->setPos(point.x() + 50, point.y()+50);  scene->addItem(light2);
        light3->setPos(point.x() - 80, point.y()-70);  scene->addItem(light3);
        light4->setPos(point.x() - 80, point.y()+50);  scene->addItem(light4);

        auto controller = new traffic_lights_controller(this);
        controller->addIntersection(light1, light4, light2, light3); // pion
        lights_controllers.push_back(controller);
        controller->setPosition(point.x(), point.y());
        }
        counter++;
    }


    int a = 0;

    car* car1 = new car(lights_controllers);
    car1->setPos(0, 320);
    scene->addItem(car1);
    car1->addControllers(lights_controllers);




    QTimer* anim = new QTimer(this);
    connect(anim, &QTimer::timeout, this, [=](){
        car1->move();
    });
    anim->start(30);
}



MainWindow::~MainWindow()
{
}

