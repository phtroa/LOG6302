#include "Specialite.h"

Specialite::Specialite()
{
}


Specialite::~Specialite()
{
}

Specialite::Specialite(char domaine, unsigned int niveau): domaine_(domaine), niveau_(niveau)
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

void Specialite::modifierDomaine(char domaine)
{
	domaine_ = domaine;
}

void Specialite::modifierNiveau(unsigned int niveau)
{
	niveau_ = niveau;
}

void Specialite::afficherInformation() const
{
	int foo = 0;
	for (size_t i = 0; i < niveau_; i++)
	{
		foo++;
	}
	int bar = 0;
	for (size_t i = 0; i < espace_niveau; i++)
	{
		bar += ++foo;
	}

}
