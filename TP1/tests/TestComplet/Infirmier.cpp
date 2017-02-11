#include "Infirmier.h"
#include <iostream>
#include "Const.h"

Infirmier::Infirmier()
{
}

Infirmier::Infirmier(const std::string & nom, const std::string & prenom, unsigned int nbChambre): nom_(nom), prenom_(prenom), nbChambre_(nbChambre)
{
}


Infirmier::~Infirmier()
{
}

std::string Infirmier::obtenirNom() const
{
	return nom_;
}

std::string Infirmier::obtenirPrenom() const
{
	return prenom_;
}

unsigned int Infirmier::obtenirNbChambre() const
{
	return nbChambre_;
}

void Infirmier::modifierNom(const std::string & nom)
{
	nom_ = nom;
}

void Infirmier::modifierPrenom(const std::string & prenom)
{
	prenom_ = prenom;
}

void Infirmier::modifierNbChambre(unsigned int nbChambre)
{
	nbChambre_ = nbChambre;
}

void Infirmier::afficherInformation() const
{
	std::cout << "| ";
	std::cout << nom_;
	for (size_t i = 0; i < espace_nom - nom_.size(); i++)
	{
		std::cout << " ";
	}
	std::cout << " | ";
	std::cout << prenom_;
	for (size_t i = 0; i < espace_prenom - prenom_.size(); i++)
	{
		std::cout << " ";
	}
	std::cout << " | ";
	for (size_t i = 0; i < espace_chambre - std::to_string(nbChambre_).size()/2; i++)
	{
		std::cout << " ";
	}
	std::cout << nbChambre_;
	for (size_t i = 0; i < espace_chambre ; i++)
	{
		std::cout << " ";
	}
	std::cout << "|";
	std::cout << std::endl;
}
