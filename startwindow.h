#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QLabel>

class QSpinBox;
class QPushButton;

class startWindow : public QDialog
{
    Q_OBJECT
public:
    startWindow(QWidget* parent = nullptr);

    int getNbOfCars() const;
    int getNbOfPedestrians() const;
private:
    QSpinBox* carCountSpin;
    QSpinBox* PedestrianCountSpin;
};

#endif // STARTWINDOW_H
