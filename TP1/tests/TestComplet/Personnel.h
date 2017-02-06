/**********************************************
 * Titre: Travail pratique #1 - Personnel.h
 * Date: 25 aout 2012
 * Auteur: 
 *********************************************/

#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <string>

#include "Medecin.h"
#include "Infirmier.h"

using namespace std;

class Personnel
{
public:
	// Constructeur par defaut
	Personnel();

	// Destructeur
	~Personnel();
	
	// Methodes publiques
	void ajouterMedecin(const Medecin& unMedecin);
	void ajouterInfirmier(const Infirmier& unInfirmier);
	
        void afficherMedecins() const;
        void afficherInfirmiers() const;
	
	void afficherEgal(int nombre) const;
	void afficherEspace(int nombre) const;

private:

	// Variables privees
	Medecin*   tableauMedecins_;
	Infirmier* tableauInfirmiers_;

	unsigned int compteurMedecin_;
	unsigned int compteurInfirmier_;

	unsigned int capaciteTableauMedecins_;
	unsigned int capaciteTableauInfirmiers_;

};

#endif
