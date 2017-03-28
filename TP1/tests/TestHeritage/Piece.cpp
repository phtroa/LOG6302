
/********************************************
* Titre: Travail pratique #3 - Piece.cpp
* Date:
* Auteur:
*******************************************/

#include "Piece.h"

Piece::Piece() :id_("defaultId"), couleur_("blanc"), positionX_(0), positionY_(0) {
}

Piece::Piece(string id, string couleur, int positionX, int positionY) {
	id_ = id;
	couleur_ = couleur;
	positionX_ = positionX;
	positionY_ = positionY;
}

Piece::~Piece() {

}

string Piece::obtenirId() const  {
	return id_;
}


void Piece::modifierId(string id) {
	id_ = id;
}

string Piece::obtenirCouleur() const {
	return couleur_;
}

void Piece::modifierCouleur(string couleur) {
	couleur_ = couleur;
}

int Piece::obtenirPositionX() const {
	return positionX_;
}

void Piece::modifierPositionX(int x) {
	positionX_ = x;
}

int Piece::obtenirPositionY() const {
	return positionY_;
}

void Piece::modifierPositionY(int y) {
	positionY_ = y;
}

bool Piece::estMouvementValide(int toX, int toY) {
	if (toX == positionX_ && toY == positionY_) {
		cout << "Deplacement de la piece non autorise" << endl;
		return false; //cannot move nothing
	}
	if (toX < 0 || toX > 7 || toY < 0 || toY > 7) {
		cout << "Deplacement de la piece non autorise" << endl;
		return false;
	}		
	return true;
}
