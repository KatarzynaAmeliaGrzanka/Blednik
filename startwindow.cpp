#include "startwindow.h"


#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>

startWindow::startWindow(QWidget* parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

        carCountSpin = new QSpinBox(this);
        carCountSpin->setRange(1, 5);
        carCountSpin->setValue(1);

        PedestrianCountSpin = new QSpinBox(this);
        PedestrianCountSpin->setRange(1, 5);
        PedestrianCountSpin->setValue(1);

        QLabel* carLabel = new QLabel("Wybierz liczbę samochodów:", this);
        QLabel* pedestrianLabel = new QLabel("Wybierz liczbę przechodniów:", this);


        QPushButton* startButton = new QPushButton("Zacznij symulację", this);
        connect(startButton, &QPushButton::clicked, this, &QDialog::accept);

        layout->addWidget(carLabel);
        layout->addWidget(carCountSpin);
        layout->addWidget(pedestrianLabel);
        layout->addWidget(PedestrianCountSpin);
        layout->addWidget(startButton);




}

int startWindow::getNbOfCars() const {
    return carCountSpin->value();
}

int startWindow::getNbOfPedestrians() const
{
    return PedestrianCountSpin->value();
}
