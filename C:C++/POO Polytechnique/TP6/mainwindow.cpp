#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

#include "Routeur.h"
#include "ObjetConnecte.h"
#include "Cellulaire.h"
#include "Chauffage.h"
#include "Meteo.h"
#include "enumTypes.h"
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <cmath>

using namespace std;

// Ne pas toucher cette classe, sauf si vous voulez ajouter certains controles avec les touches.
// La classe QGraphicsScene a ete surchargee pour avoir un controle a partir des boutons de la souris.
class GraphicsScene : public QGraphicsScene
{
public:
    explicit GraphicsScene(qreal x, qreal y, qreal width, qreal height, MainWindow* mainWindow_param, QObject * parent = 0) :
        QGraphicsScene(x, y, width, height, parent)
    {
        this->setBackgroundBrush(Qt::gray);
        mainWindow = mainWindow_param;
    }

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
    {
        if(mouseEvent->button() == Qt::LeftButton)
            mainWindow->getVoiture()->avance();
        else if(mouseEvent->button() == Qt::RightButton)
            mainWindow->getVoiture()->recule();
        mainWindow->getSlider()->setSliderPosition(mainWindow->getVoiture()->getPositionChemin());

        QGraphicsScene::mouseReleaseEvent(mouseEvent);
    }

private:
    MainWindow* mainWindow;
};


// Constructeur de la classe MainWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Construction de l'environnement graphique.
    // Le contenu de cette fonction doit etre modifie.
    setUI();

    // Creer un routeur
    routeur = new Routeur();

    // Creer une maison, avec l'ID 1, une adresse et la position 50.
    // Ajouter la maison aux connexions du routeur
    maison = new Maison(1, "2500 Chemin Polytechnique", 50, "Montreal");
    maison->seConnecter(routeur);

    // Creer un objet Meteo et ajouter la maison a sa liste d'observateurs.
    meteo = new Meteo();
    meteo->ajouterVille("Montreal", 14, 15);
    meteo->ajouterObservateur(maison);

    // Creer 4 personnes: Philippe Lafrite
    philippe = new Personne("Philippe", "Lafrite", 55, NEUTRE);

    // Creer un cellulaire pour chaque occupant
    // Ajouter la maison dans la liste des observateurs de chaque cellulaire.
    cellulairePhilippe = new Cellulaire(2, "514-430-9999");
    cellulairePhilippe->setProprietaire(philippe);
    cellulairePhilippe->ajouterObservateur(maison);
    philippe->attribuerCellulaire("514-430-9999");

    // Modifier la position du cellulaire de Philippe a 0 et ajouter le cellulaire de Philippe a la voiture
    cellulairePhilippe->setPosition(0);
    item_voiture->setCellulaire(cellulairePhilippe);

    // Ajouter Philippe et Mathilde comme occupants de la maison
    // Lorsqu'on ajoute un occupant a la maison, son cellulaire doit egalement etre ajoute.
    maison->ajouterOccupant(philippe);

    // Créer 1 chauffage automatique et le connecter au routeur
    // Attention à ne pas attribuer un ID similaire aux IDs déjà attribués(commencer à 5)
    chauffage = new Chauffage(3);
    chauffage->setAutomatique(true);
    chauffage->seConnecter(routeur);

    // Changer la temperature exterieure de Montreal a 24 degres (en utilisant l'objet Meteo)
    // ReChanger la temperature exterieure de Montreal a 18 degres
    cout << endl << "Changement de temperature Montreal : 24" << endl;
    meteo->setTemp("Montreal", 24);
    cout << endl << "Changement de temperature Montreal : 18" << endl;
    meteo->setTemp("Montreal", 18);

    setConnection();
}

/* !!!!!!!!!! A FAIRE !!!!!!!!!!!!
* Etablissement des connections entre les objets.
* Trois signaux doivent etre crees:
* - signal provenant du slider et fonction permettant le deplacement de la voiture
* - signal provenant de la maison et affichant l'info-bulle
* - signal provenant de la maison et cachant l'info-bulle
*/
void MainWindow::setConnection() {
    QObject::connect(slider_, SIGNAL(valueChanged(int)),this, SLOT(bouge_voiture(int)));
    QObject::connect(maison, SIGNAL(signal_bonjour()), this, SLOT(afficher_message()));
    QObject::connect(maison, SIGNAL(signal_aurevoir()), this, SLOT(cacher_message()));
}

// Construction de l'interface graphique
void MainWindow::setUI() {
    setFixedSize(1000, 800);

    // Creation de l'environnement graphique
    GraphicsScene* scene = new GraphicsScene(0,0,970,697, this);
    QGraphicsView* view = new QGraphicsView( scene );

    // Creation de la carte et ajout a la scene
    QImage image(":/Images/map.png");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);

    // Creation d'une voiture et ajout a la scene
    // La voiture a un chemin predetermine.
    QImage image_voiture(":/Images/voiture.png");
    item_voiture = new Voiture(QPixmap::fromImage(image_voiture));
    scene->addItem(item_voiture);

    // Creation d'une info-bulle, qui sera affichee lors de certains evenements
    ellipse_ = scene->addEllipse(70, 200, 200, 60, QPen(), QBrush(Qt::white, Qt::SolidPattern));
    text_ = scene->addText("Bonjour !", QFont("Helvetica", 32 ));
    text_->setPos(105, 212);
    ellipse_->hide();
    text_->hide();

    // Ajout de la scene au layout
    QHBoxLayout *display_layout = new QHBoxLayout;
    display_layout->addWidget(view);

    // Creation d'une ligne separatrice en utilisant QFrame::HLine
    QFrame* line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);


    // !!!!!!!!!! A FAIRE !!!!!!!!!!!!
    // 1. Creation d'un slider (widget QSlider) dont la valeur minimal est 0 et la valeur maximale est 113
    slider_ = new QSlider(this);
    slider_->setMinimum(0);
    //Le slider est mis à 114 (et pas 113) pour lancer l'exception et vérifier qu'elle fonctionne bien
    slider_->setMaximum(114);
    slider_->setOrientation(Qt::Horizontal);

    // 2. Creation d'un label (widget QLabel) indiquant le texte suivant: "Controle de la voiture:"
    QLabel* label = new QLabel(this);
    label->setText("Controle de la voiture");

    // 3. Ajout des widgets slider et label dans un layout de type boite horizontale
    QHBoxLayout* hbox = new QHBoxLayout;
    hbox->addWidget(slider_);
    hbox->addWidget(label);

    // 4. Creation du layout principal, de type QVBoxLayout et ajouter le layout de la carte (display_layout), la ligne horizontale et le layout contenant le slider
    QVBoxLayout* primary_layout = new QVBoxLayout;
    primary_layout->addLayout(display_layout);
    primary_layout->addWidget(line);
    primary_layout->addLayout(hbox);


    // La fin de cette fonction n'est pas a modifier
    // Creation du widget principal, contenant le layout principal
    QWidget *widget = new QWidget(this);
    widget->setLayout(primary_layout);

    // Attribution du widget principal a la fenetre
    setCentralWidget(widget);

    // Titre de l'application
    setWindowTitle("LaFrite Mobile");
}

void MainWindow::bouge_voiture(int position)
{
    item_voiture->change_position(position);
}

// Affiche de l'info-bulle
void MainWindow::afficher_message()
{
    ellipse_->show();
    text_->show();
}

// Cache l'info-bulle
void MainWindow::cacher_message()
{
    ellipse_->hide();
    text_->hide();
}

// Destructeur de la fenetre
MainWindow::~MainWindow()
{
    delete slider_;
    delete ellipse_;
    delete text_;
    delete item_voiture;

    delete philippe;
    delete cellulairePhilippe;
    delete maison;
    delete routeur;
    delete meteo;
    delete chauffage;
}
