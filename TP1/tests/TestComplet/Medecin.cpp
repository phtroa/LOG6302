/********************************************
 * Titre: Travail pratique #1 - Medecin.cpp
 * Date: 25 aout 2012
 * Auteur: 
 *******************************************/

#include"Medecin.h"
#include <iostream>
#include "Const.h"

Medecin::Medecin():nom_(), horaires_(0), specialite_(nullptr)
{
}

Medecin::Medecin(const string& nom, int horaires, Specialite * uneSpecialite): nom_(nom), horaires_(horaires), specialite_(uneSpecialite)
{
}

Medecin::~Medecin()
{
	
}

string Medecin::obtenirNom() const
{
	return nom_;
}

int Medecin::obtenirHoraires() const
{
	return horaires_;
}

Specialite Medecin::obtenirSpecialite() const
{
	return *specialite_;
}

void Medecin::modifierNom(const string& nom)
{
	nom_ = nom;
}

void Medecin::modifierHoraires(int horaires)
{
	horaires_ = horaires;
}

void Medecin::modifierSpecialite( Specialite * specialite)
{
	specialite_ = specialite;
}

void Medecin::afficherInformation() const
{
	std::cout << "| ";
	std::cout << nom_;
	for (size_t i = 0; i < espace_nom - nom_.size(); i++)
	{
		cout << " ";
	}
	cout << " | ";
	for (size_t i = 0; i < espace_horaires - to_string(horaires_).size(); i++)
	{
		cout << " ";
	}
	cout << horaires_;
	for (size_t i = 0; i < espace_horaires; i++)
	{
		cout << " ";
	}
	specialite_->afficherInformation();
}

