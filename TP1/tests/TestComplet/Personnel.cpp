/**********************************************
 * Titre: Travail pratique #1 - Personnel.cpp
 * Date: 10 janvier 2017
 * Auteur: 
 *********************************************/



#include "Medecin.h"
#include "Infirmier.h"
#include "Personnel.h"
#include <iostream>
#include "Const.h"
Personnel::Personnel():compteurMedecin_(0), compteurInfirmier_(0), capaciteTableauMedecins_(3), capaciteTableauInfirmiers_(3)
{
	tableauInfirmiers_ = new Infirmier[capaciteTableauInfirmiers_];
	tableauMedecins_ = new Medecin[capaciteTableauMedecins_];
}

Personnel::~Personnel()
{
	delete[] tableauInfirmiers_;
	delete[] tableauMedecins_;
}
	
void Personnel::ajouterMedecin(const Medecin& unMedecin)
{
	if (compteurMedecin_ >= capaciteTableauMedecins_) {
		capaciteTableauMedecins_ *= 2;
		Medecin* nouveauTableauMedecins = new Medecin[capaciteTableauMedecins_];
		for (size_t i = 0; i < compteurMedecin_; i++)
		{
			nouveauTableauMedecins[i] = tableauMedecins_[i];
		}
		delete [] tableauMedecins_;
		tableauMedecins_ = nullptr;
		tableauMedecins_ = nouveauTableauMedecins;
	}
	tableauMedecins_[compteurMedecin_] = unMedecin;
	compteurMedecin_++;
}

void Personnel::ajouterInfirmier(const Infirmier& unInfirmier)
{
	if (compteurInfirmier_ >= capaciteTableauInfirmiers_) {
		capaciteTableauInfirmiers_ *= 3;
		Infirmier* nouveauTableauInfirmiers = new Infirmier[capaciteTableauInfirmiers_];
		for (size_t i = 0; i < compteurInfirmier_; i++)
		{
			nouveauTableauInfirmiers[i] = tableauInfirmiers_[i];
		}
		delete[] tableauInfirmiers_;
		tableauInfirmiers_ = nullptr;
		tableauInfirmiers_ = nouveauTableauInfirmiers;
	}
	tableauInfirmiers_[compteurInfirmier_] = unInfirmier;
	compteurInfirmier_++;
}
	
void Personnel::afficherMedecins() const
{
	afficherEgal(espacement_medecin / 2);
	std::string tabMed = "Tableau Medecins";
	cout << tabMed;
	afficherEgal(espacement_medecin / 2);
	cout << endl;
	afficherEgal(espacement_medecin + tabMed.size());
	cout << endl;
	string nom = "nom";
	string horaires = "horaires";
	string domaine = "Domaine Specialite";
	string niveau = "Niveau Specialite";
	cout << "| " << nom;
	afficherEspace(espace_nom - nom.size());
	cout << " | " << horaires;
	afficherEspace(2*espace_horaires - horaires.size());
	cout << " | " << domaine;
	afficherEspace(espace_domaine - domaine.size());
	cout << " | ";
	afficherEspace(espace_niveau - niveau.size() / 2);
	cout << niveau;
	afficherEspace(espace_niveau - niveau.size() / 2);
	cout << "| " << endl;
	
	for (size_t i = 0; i < compteurMedecin_; i++)
	{
		tableauMedecins_[i].afficherInformation();
		cout << endl;
	}
	afficherEgal(espacement_medecin + tabMed.size());
	cout << endl;
}

void Personnel::afficherInfirmiers() const
{
	afficherEgal(espacement_infirmier/2);
	std::string tabInf = "Tableau Infimiers";
	cout << tabInf;
	afficherEgal(espacement_infirmier/2);
	cout << endl;
	afficherEgal(espacement_infirmier + tabInf.size());

	string nom = "nom";
	string prenom = "prenom";
	string nombreChambre = "Nombre de Chambre";
	cout << endl << "| " << nom;
	afficherEspace(espace_nom - nom.size());
	cout << " | " << prenom;
	afficherEspace(espace_prenom - prenom.size());
	cout << " | ";
	cout << nombreChambre;
	afficherEspace(2 * espace_chambre - nombreChambre.size());
	cout << " | " << endl;
	for (size_t i = 0; i < compteurInfirmier_; i++)
	{
		tableauInfirmiers_[i].afficherInformation();
	}
	afficherEgal(espacement_infirmier + tabInf.size());
}

void Personnel::afficherEgal(int nombre) const
{
	for (size_t i = 0; i < nombre; i++)
	{
		cout << "=";
	}
}

void Personnel::afficherEspace(int nombre) const
{
	for (size_t i = 0; i < nombre; i++)
	{
		cout << " ";
	}
}


