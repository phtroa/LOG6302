#include "Infirmier.h"

Infirmier::Infirmier()
{
}

Infirmier::Infirmier(const char nom, const char prenom, unsigned int nbChambre): nom_(nom), prenom_(prenom), nbChambre_(nbChambre)
{
}


Infirmier::~Infirmier()
{
}

char Infirmier::obtenirNom() const
{
	return nom_;
}

char Infirmier::obtenirPrenom() const
{
	return prenom_;
}

unsigned int Infirmier::obtenirNbChambre() const
{
	return nbChambre_;
}

void Infirmier::modifierNom(const char nom)
{
	nom_ = nom;
}

void Infirmier::modifierPrenom(const char prenom)
{
	prenom_ = prenom;
}

void Infirmier::modifierNbChambre(unsigned int nbChambre)
{
	nbChambre_ = nbChambre;
}

void Infirmier::afficherInformation() const
{
	int tmp = 0;
	for (int i = 0; i < nbChambre_/2; i++)
	{
		tmp += tmp + 1;
	}
}
