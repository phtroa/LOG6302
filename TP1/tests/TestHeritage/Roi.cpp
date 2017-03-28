
/********************************************
* Titre: Travail pratique #3 - Roi.cpp
* Date:
* Auteur:
*******************************************/

#include "Roi.h"

Roi::Roi(): Piece("defaultId", "blanc", 0, 0) {}

Roi::Roi(string id, string couleur, int positionX, int positionY) : Piece( id,  couleur, positionX, positionY) {
}

bool Roi::estMouvementValide(int toX, int toY)  {
	if (!Piece::estMouvementValide(toX, toY))
		return false;	
	if (abs(obtenirPositionX() - toX) == 1 && abs(obtenirPositionY() - toY) == 1 ||
		abs(obtenirPositionX() - toX) == 0 && abs(obtenirPositionY() - toY) == 1 ||
		abs(obtenirPositionX() - toX) == 1 && abs(obtenirPositionY() - toY) == 0)
		return true;
	else
		return false;
}

Roi::~Roi() {}

void Roi::deplacer(int toX, int toY){
	if (estMouvementValide(toX, toY)) {
		cout << "Déplacement du Roi" << obtenirId() << " de la position ("
			<< obtenirPositionX() << "," << obtenirPositionY() << ")" << " a la position ("
			<< obtenirPositionX() << "," << obtenirPositionY() << ")"<<endl;
		modifierPositionX(toX);
		modifierPositionX(toY);		 
	}else{
		cout << "Deplacement du Roi non autorisée";
	}
}