#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "traffic_lights_controller.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsScene* scene;
    std::vector<traffic_lights_controller*> controllers;
};
#endif // MAINWINDOW_H
