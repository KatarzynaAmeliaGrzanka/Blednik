#include "startwindow.h"


#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>

startWindow::startWindow(QWidget* parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

        m_carCountSpin = new QSpinBox(this);
        m_carCountSpin->setRange(1, 5);
        m_carCountSpin->setValue(1);

        m_PedestrianCountSpin = new QSpinBox(this);
        m_PedestrianCountSpin->setRange(1, 5);
        m_PedestrianCountSpin->setValue(1);

        QLabel* carLabel = new QLabel("Wybierz liczbę samochodów:", this);
        QLabel* pedestrianLabel = new QLabel("Wybierz liczbę przechodniów:", this);


        QPushButton* startButton = new QPushButton("Zacznij symulację", this);
        connect(startButton, &QPushButton::clicked, this, &QDialog::accept);

        layout->addWidget(carLabel);
        layout->addWidget(m_carCountSpin);
        layout->addWidget(pedestrianLabel);
        layout->addWidget(m_PedestrianCountSpin);
        layout->addWidget(startButton);




}

int startWindow::getNbOfCars() const {
    return m_carCountSpin->value();
}

int startWindow::getNbOfPedestrians() const
{
    return m_PedestrianCountSpin->value();
}
