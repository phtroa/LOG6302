#include "Specialite.h"
#include <iostream>
#include "Const.h"

Specialite::Specialite()
{
}


Specialite::~Specialite()
{
}

Specialite::Specialite(const std::string & domaine, unsigned int niveau): domaine_(domaine), niveau_(niveau)
{
}

std::string Specialite::obtenirDomaine() const
{
	return domaine_;
}

unsigned int Specialite::obtenirNiveau() const
{
	return niveau_;
}

void Specialite::modifierDomaine(const std::string & domaine)
{
	domaine_ = domaine;
}

void Specialite::modifierNiveau(unsigned int niveau)
{
	niveau_ = niveau;
}

void Specialite::afficherInformation() const
{
	std::cout << " | ";
	std::cout << domaine_;
	for (size_t i = 0; i < espace_domaine - domaine_.size(); i++)
	{
		std::cout << " ";
	}
	std::cout << " | ";
	for (size_t i = 0; i < espace_niveau - std::to_string(niveau_).size(); i++)
	{
		std::cout << " ";
	}
	std::cout << niveau_;
	for (size_t i = 0; i < espace_niveau; i++)
	{
		std::cout << " ";
	}
	std::cout << " | ";

}
