#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QtGui>
#include <QMainWindow>

#include <QSlider>

#include "Routeur.h"
#include "Chauffage.h"
#include "Meteo.h"
#include "voiture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Voiture* getVoiture() { return item_voiture; }
    QSlider* getSlider() { return slider_; }

public slots:
    void bouge_voiture(int position);
    void afficher_message();
    void cacher_message();

private:
    // Ne pas changer. Construit l'interface
    void setUI();
    void setConnection();

    QSlider* slider_;
    QGraphicsEllipseItem* ellipse_;
    QGraphicsTextItem* text_;

    Voiture* item_voiture;

    Routeur* routeur;
    Maison *maison;
    Meteo* meteo;
    Chauffage* chauffage;
    Personne* philippe;
    Cellulaire* cellulairePhilippe;
};

#endif // MAINWINDOW_H
