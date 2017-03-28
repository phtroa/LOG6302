
/********************************************
* Titre: Travail pratique #3 - Pion.cpp
* Date:
* Auteur:
*******************************************/

#include "Pion.h"


Pion::Pion():Piece("defaultId","blanc",0,0),estPositionInitiale_(true){
}


Pion::Pion(string id, string couleur, int positionX, int positionY) : Piece(id, couleur, positionX, positionY) {
	estPositionInitiale_ = true;
}

Pion::~Pion() {
}



bool Pion::obtenirEstPositionInitiale() const{
	return estPositionInitiale_;
}

void Pion::setEstPositionInitiale(bool estPositionInitiale) {
	estPositionInitiale_ = estPositionInitiale;
}


bool Pion::estMouvementValide(int toX, int toY) {
	if (!Piece::estMouvementValide(toX, toY))
		return false;
	if (obtenirCouleur() == "blanc") {
		if (obtenirEstPositionInitiale()) {
			if (((toY - obtenirPositionY()) <= 2) && (toX == obtenirPositionX()) && (toY > obtenirPositionY())) {
				return true;
			}
		}
		else
		{
			if ((toY - obtenirPositionY()) <= 1 && (toX == obtenirPositionX()) && toY > obtenirPositionY()) {
				return true;
			}
		}
		}
	if (obtenirCouleur() == "noir") {
		if (obtenirEstPositionInitiale()) {
			if (((toY - obtenirPositionY()) <= 2) && (toX == obtenirPositionX()) && (toY < obtenirPositionY())) {
				return true;
			}
		}
		else
		{
			if (((toY - obtenirPositionY()) <= 1) && (toX == obtenirPositionX()) && (toY < obtenirPositionY())) {
				return true;
			}
		}
		}
	
	return false;
	
}

void Pion::deplacer(int toX, int toY) {
	if (estMouvementValide(toX, toY)) {
		cout << "Deplacement du Pion " << obtenirId() << " de la position ("
			<< obtenirPositionX() << "," << obtenirPositionY() << ")" << " a la position ("
			<< toX << "," << toY << ")"<<endl;
		modifierPositionX(toX);
		modifierPositionX(toY);
		estPositionInitiale_ = false;
	}else{
		cout << "Deplacement du Pion non autorise " << endl ;
	}
}