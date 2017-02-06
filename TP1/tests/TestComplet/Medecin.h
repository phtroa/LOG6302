/********************************************
 * Titre: Travail pratique #1 - Medecin.h
 * Date: 25 aout 2012
 * Auteur: 
 *******************************************/

#ifndef MEDECIN_H
#define MEDECIN_H

#include <string>
#include "Specialite.h"

using namespace std;

//const unsigned int NB_MEDECIN = 6;

class Medecin 
{
public:
	// Constructeurs par defaut et par parametre
	Medecin();
	Medecin(const string& nom, int horaires, Specialite* uneSpecialite);
	
	// Destructeur
	~Medecin();
	
	// Methodes d'acces
	string obtenirNom() const;
	int obtenirHoraires() const;
	Specialite obtenirSpecialite() const;
	
	// Methodes de modification
	void modifierNom(const string& nom);
	void modifierHoraires(int horaires);
	void modifierSpecialite(Specialite* specialite);

	void afficherInformation() const;

private:

	// Variables privees
	string nom_;
	int horaires_;
	Specialite* specialite_;
};

#endif
