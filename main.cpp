#include "mainwindow.h"
#include "startwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    startWindow start;

    if (start.exec() == QDialog::Accepted) {
            int carCount = start.getNbOfCars();
            int PedestrianCount = start.getNbOfPedestrians();

            MainWindow w(carCount, PedestrianCount);
            w.show();
            return a.exec();
        }
    return a.exec();
}
