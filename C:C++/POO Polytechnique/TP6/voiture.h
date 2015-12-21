#ifndef VOITURE_H
#define VOITURE_H

#include <QGraphicsPixmapItem>
#include <QMessageBox>

#include <vector>
#include <stdexcept>
#include <iostream>
#include "Cellulaire.h"

using namespace std;

class Voiture : public QGraphicsPixmapItem
{
public:
    Voiture(const QPixmap & pixmap, QGraphicsItem * parent = 0) : QGraphicsPixmapItem(pixmap, parent)
    {
        // Initialisation de la voiture et de son origine (utile pour les deplacement)
        size_voiture_ = pixmap.size();
        setTransformOriginPoint(QPointF(size_voiture_.width()/2.0, size_voiture_.height()/2.0));

        // Initialisation du chemin, contenant 114 points
        // Ce chemin est propre a la voiture et ne peut etre change
        QPointF chemin_init[114] = {QPointF(38,630), QPointF(71,627), QPointF(92,625), QPointF(111,623), QPointF(127,622), QPointF(144,620), QPointF(160,620), QPointF(175,619), QPointF(190,617), QPointF(207,616), QPointF(223,616), QPointF(241,613), QPointF(252,611), QPointF(265,609), QPointF(278,607), QPointF(293,604), QPointF(306,604), QPointF(321,601), QPointF(330,600), QPointF(335,590), QPointF(338,581), QPointF(340,572), QPointF(344,563), QPointF(347,553), QPointF(351,543), QPointF(353,531), QPointF(358,520), QPointF(360,511), QPointF(362,503), QPointF(364,494), QPointF(367,486), QPointF(371,474), QPointF(374,467), QPointF(376,457), QPointF(380,448), QPointF(384,437), QPointF(387,427), QPointF(391,415), QPointF(395,402), QPointF(399,390), QPointF(402,381), QPointF(405,372), QPointF(408,363), QPointF(412,353), QPointF(415,346), QPointF(416,336), QPointF(418,326), QPointF(423,318), QPointF(427,307), QPointF(432,297), QPointF(435,288), QPointF(438,279), QPointF(440,269), QPointF(443,258), QPointF(448,247), QPointF(452,238), QPointF(456,225), QPointF(458,217), QPointF(460,210), QPointF(462,201), QPointF(465,190), QPointF(468,182), QPointF(471,171), QPointF(474,160), QPointF(479,150), QPointF(481,137), QPointF(484,126), QPointF(487,116), QPointF(490,105), QPointF(494,95), QPointF(497,83), QPointF(500,74), QPointF(503,65), QPointF(506,58), QPointF(517,60), QPointF(526,61), QPointF(534,63), QPointF(543,65), QPointF(553,67), QPointF(563,69), QPointF(574,71), QPointF(583,74), QPointF(594,77), QPointF(603,81), QPointF(614,84), QPointF(625,87), QPointF(633,89), QPointF(644,91), QPointF(654,95), QPointF(663,100), QPointF(674,103), QPointF(687,108), QPointF(696,111), QPointF(706,115), QPointF(719,117), QPointF(729,121), QPointF(741,124), QPointF(750,127), QPointF(760,131), QPointF(771,133), QPointF(784,137), QPointF(794,141), QPointF(805,144), QPointF(816,149), QPointF(826,151), QPointF(837,156), QPointF(849,159), QPointF(860,162), QPointF(871,165), QPointF(880,168), QPointF(892,171), QPointF(903,176), QPointF(912,180), QPointF(924,183)};
        for (int i=0; i<114; i++) {
            double angle;
            if (i < 19) angle = -6;
            else if (i < 73) angle = -72;
            else angle = 18;
            chemin.push_back(make_pair(chemin_init[i], angle));
        }

        // Initilisation de la position de la voiture
        move(chemin[0].first);
        rotate(chemin[0].second);
    }

    // Accesseurs et modificateurs
    int getPositionChemin() { return cell_->getPosition(); }
    void setCellulaire(Cellulaire* cell) { cell_ = cell; }
    Cellulaire* getCellulaire() { return cell_; }

    // Fonction permettant de faire avancer la voiture
    void avance()
    {
        int position = cell_->getPosition();
        position++;
        change_position(position);
    }

    // Fonction permettant de faire reculer la voiture
    void recule()
    {
        int position = cell_->getPosition();
        position--;
        change_position(position);
    }

    // Fonction permettant de modifier la position de la voiture.
    // La position de la voiture est un entier allant de 0 a 114, correspondant à la position dans le vecteur "chemin".
    // Le chemin contient les coordonnées et l'angle que la voiture doit avoir pour suivre la route.
    // !!!!!!!!!! A FAIRE !!!!!!!!!!!!
    // Vous devez modifier cette fonction pour qu'elle tienne ne permette pas a la voiture d'aller plus loin que ce que le chemin le permet.
    // Vous devez utiliser un systeme d'exception pour verifier que vous pouvez acceder a un element du vecteur et afficher un message d'erreur (QMessageBox).
    // Indice: exception "out_of_range"
    void change_position(int position)
    {
        try{
            move(chemin.at(position).first);
            rotate(chemin.at(position).second);
            cell_->setPosition(position);
        } catch (const std::out_of_range& oor){
            QMessageBox error;
            error.setText("Vous ne pouvez pas aller plus loin !");
            error.exec();
        }
    }

private:
    // Fonction deplacant la voiture a une position indiquee en parametre
    void move(QPointF position)
    {
        setPos(QPointF(position.x()-(size_voiture_.width()/2), position.y()-(size_voiture_.height()/2)));
    }

    // Fonction permettant d'effectuer une rotation a la voiture
    void rotate(double angle)
    {
        setRotation(angle);
    }

    QSize size_voiture_;

    Cellulaire* cell_;

    vector< pair<QPointF, double> > chemin;
};

#endif // VOITURE_H
