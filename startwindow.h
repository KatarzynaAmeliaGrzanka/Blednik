#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QLabel>

class QSpinBox;
class QPushButton;

/**
 * @brief The startWindow class
 * Klasa okna startowego, gdzie użytkownik podaje liczbę samochodów i pieszych.
 */

class startWindow : public QDialog
{
    Q_OBJECT
public:
    startWindow(QWidget* parent = nullptr);

    /**
     * @brief getNbOfCars Metoda zwracająca liczbę samochodów w symulacji.
     * @return
     */
    int getNbOfCars() const;
    /**
     * @brief getNbOfPedestrians Metoda zwracająca liczbę pieszych w symulacji.
     * @return
     */
    int getNbOfPedestrians() const;
private:
    /**
     * @brief carCountSpin wskaźnik do widgeta Qt typu QSpinBox, liczba samochodów
     */
    QSpinBox* m_carCountSpin;
    /**
     * @brief PedestrianCountSpin wskaźnik do widgeta Qt typu QSpinBox, liczba samochodów
     */
    QSpinBox* m_PedestrianCountSpin;
};

#endif // STARTWINDOW_H
