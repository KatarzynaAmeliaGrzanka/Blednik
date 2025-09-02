#include "mainwindow.h"
#include <QGraphicsView>
#include "map.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , scene(new QGraphicsScene(this))
{

    // Widok
    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);

    map map(1200, 940);

    resize(map.getMapWidth(),map.getMapHeight());
    scene->setSceneRect(0,0,map.getMapWidth(),map.getMapHeight());

    map.setRoadWidth(80);
    map.setHorizontalRoad(300);
    map.setHorizontalRoad(600);
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
}

MainWindow::~MainWindow()
{
}

