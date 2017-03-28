
/********************************************
* Titre: Travail pratique #3 - Pion.h
* Date:
* Auteur:
*******************************************/

#pragma once

#ifndef PION_H
#define PION_H


#include "Piece.h"
#include <string>

using namespace std;

class Pion : public Piece {

private: 
	bool estPositionInitiale_;


public:
	// Constructeurs
	Pion();
	Pion(string id, string couleur, int positionX, int positionY);

	// Destructeur
	~Pion();
	
	bool obtenirEstPositionInitiale() const;
	void setEstPositionInitiale(bool estPositionInitiale);

	bool estMouvementValide(int toX, int toY);
	void deplacer(int toX, int toY);

};
#endif
