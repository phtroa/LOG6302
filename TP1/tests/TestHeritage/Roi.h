
/********************************************
* Titre: Travail pratique #3 - Roi.h
* Date:
* Auteur:
*******************************************/

#pragma once

#ifndef ROI_H
#define ROI_H


#include "Piece.h"
#include <string>

using namespace std;

class Roi : public Piece{

public :
	Roi();
	Roi(string id, string couleur, int positionX, int positionY);
	~Roi();	

	bool estMouvementValide(int toX, int toY);  
	void deplacer(int toX, int toY);

};
#endif