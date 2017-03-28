
/********************************************
* Titre: Travail pratique #3 - Tour.cpp
* Date:
* Auteur:
*******************************************/

#include "Tour.h"

Tour::Tour() :Piece("defaultId", "blanc", 0, 0){}

Tour::Tour(string id, string couleur, int positionX, int positionY) : Piece(id, couleur, positionX, positionY){}

Tour::~Tour(){}


bool Tour::estMouvementValide(int toX, int toY) {
	if (!Piece::estMouvementValide(toX, toY))
		return false;
	if ((obtenirPositionX() == toX)  || (obtenirPositionY() == toY))		
		return true;
	else
		return false;
}

void Tour::deplacer(int toX, int toY) {
	if (estMouvementValide(toX, toY)) {
		cout << "Déplacement de la Tour " << obtenirId() << " de la position ("
			<< obtenirPositionX() << "," << obtenirPositionY() << ")" << " a la position ("
			<< toX << "," << toY << ")"<<endl;
		modifierPositionX(toX);
		modifierPositionX(toY);
	}
	else {
		cout << "Deplacement de la Tour non autorise ";
	}
}