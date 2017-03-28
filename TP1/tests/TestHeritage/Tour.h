
/********************************************
* Titre: Travail pratique #3 - Tour.h
* Date:
* Auteur:
*******************************************/

#pragma once

#ifndef TOUR_H
#define TOUR_H

#include "Tour.h"
#include "Piece.h"
#include <string>

using namespace std;

class Tour : public Piece {

public:
	// Constructeurs
	Tour();
	Tour(string id, string couleur, int positionX, int positionY);

	// Destructeur
	~Tour();
	
	bool estMouvementValide(int toX, int toY);
	void deplacer(int toX, int toY);
};
#endif