
/********************************************
* Titre: Travail pratique #3 - Echiquier.cpp
* Date: 
* Auteur:
*******************************************/

#include "Echiquier.h"

Echiquier::Echiquier(){
	tableauPions_ = new Pion[16];
	capaciteTableauPion_ = 16;
	tableauTours_ = new Tour[4];
	capaciteTableauTour_ = 4;
	compteurPion_ = 0;
	compteurTour_ = 0;
}

Echiquier::~Echiquier(){
	delete[] tableauPions_;
	delete[] tableauTours_;
	tableauPions_ = nullptr;
	tableauTours_ = nullptr;
	compteurPion_ = 0;
	compteurTour_ = 0;
}

void Echiquier::ajouterRoi(const Roi &unRoi,int position) {
	roi[position] = unRoi;
}

void Echiquier::ajouterPion(const Pion &unPion) {
	tableauPions_[compteurPion_++] = unPion;
}

void Echiquier::enleverPion(string id) {
	for (int i = 0;i < compteurPion_;i++) {
		if (tableauPions_[i].obtenirId() == id) {
			for (int j = i;j < compteurPion_-1;j++) {
				tableauPions_[j] = tableauPions_[j + 1];
			}
			compteurPion_--;
		}
	}
}

void Echiquier::ajouterTour(const Tour &uneTour) {
	tableauTours_[compteurTour_++] = uneTour;
}

void Echiquier::enleverTour(string id) {
	for (int i = 0;i < compteurTour_;i++) {
		if (tableauTours_[i].obtenirId() == id) {
			for (int j = i;j < compteurTour_ - 1;j++) {
				tableauTours_[j] = tableauTours_[j + 1];
			}
			compteurTour_--;
		}
	}
}

void Echiquier::deplacerPiece(string id, int toX, int toY) {

	for (int i = 0; i < compteurPion_; i++) {
		if (tableauPions_[i].obtenirId() == id) {
			tableauPions_[i].deplacer(toX, toY);
			//return;
		}
	}
	for (int i = 0; i < compteurTour_; i++) {
		if (tableauTours_[i].obtenirId() == id) {
			tableauTours_[i].deplacer(toX, toY);
			//return;
		}
	}
	for (int i = 0; i < 2; i++) {
		if (roi[i].obtenirId() == id) {
			roi[i].deplacer(toX, toY);
			//return;
		}
	}
}


