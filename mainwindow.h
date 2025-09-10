#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>


/**
 * @brief The MainWindow class
 * Klasa głownego okna aplikacji, gdzie wyświetlana jest symulacja.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow Konstruktor
     * @param nbOfCars Liczba samochodów w symulacji.
     * @param nbOfPedestrians Liczba pieszych w symulacji.
     * @param parent
     */
    MainWindow(int nbOfCars = 0, int nbOfPedestrians = 0, QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsScene* scene;
};
#endif // MAINWINDOW_H
