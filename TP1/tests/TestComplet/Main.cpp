/**************************************************
 * Titre: Travail pratique #1 - Main.cpp
 * Date: 25 aout 2012
 * Auteur: 
**************************************************/

#include "Specialite.h"
#include "Medecin.h"
#include "Infirmier.h"
#include "Personnel.h"

#include <string>
#include <iostream>

using namespace std;

int main()
{
	//1-  Creez un objet du type Infirmier à l'aide du constructeur par défaut
	Infirmier infirmier;
	//2-  Modifiez le nom, le prenom et le nbChambre de cet objet à l'aide des méthodes de modification
	infirmier.modifierNom("Doe");
	infirmier.modifierPrenom("John");
	infirmier.modifierNbChambre(10);
	//3-  Creez 11 autres objets du type Infirmier à l'aide du constructeur par paramètre avec des valeurs de votre choix
	Infirmier infirmier1("Tremblay", "Gilles", 2);
	Infirmier infirmier2("Labe", "Sylvie", 3);
	Infirmier infirmier3("Labelle", "Amelie", 4);
	Infirmier infirmier4("Lamontagne", "Maxime", 5);
	Infirmier infirmier5("Laflamme", "John", 6);
	Infirmier infirmier6("Lamoureux", "Julie", 7);
	Infirmier infirmier7("Langlais", "Eric", 8);
	Infirmier infirmier8("Lamarre", "Roger", 9);
	Infirmier infirmier9("Laplante", "Linda", 10);
	Infirmier infirmier10("Latour", "Hug", 11);
	Infirmier infirmier11("Lessard", "Emilie", 12);

	//4-  Creez un objet du type Personnel à l'aide du constructeur par défaut
	Personnel personnel;
	//5-  Ajoutez les 12 objets du type Infimier à tableauInfirmiers de ce dernier

	personnel.ajouterInfirmier(infirmier);
	personnel.ajouterInfirmier(infirmier1);
	personnel.ajouterInfirmier(infirmier2);
	personnel.ajouterInfirmier(infirmier3);
	personnel.ajouterInfirmier(infirmier4);
	personnel.ajouterInfirmier(infirmier5);
	personnel.ajouterInfirmier(infirmier6);
	personnel.ajouterInfirmier(infirmier7);
	personnel.ajouterInfirmier(infirmier8);
	personnel.ajouterInfirmier(infirmier9);
	personnel.ajouterInfirmier(infirmier10);
	personnel.ajouterInfirmier(infirmier11);

	//6-  Creez un objet du type Specialite à l'aide du constructeur par défaut
	Specialite* specialite = new Specialite();
	//7-  Modifiez le domaine et le niveau de cet objet à l'aide des méthodes de modification
	specialite->modifierDomaine("Chirurgie");
	specialite->modifierNiveau(15);
	//8-  Creez 5 autres objets du type Specialite à l'aide du constructeur par paramètre avec des valeurs de votre choix
	Specialite* specialite1 = new Specialite("Demartologie", 10);
	Specialite* specialite2 = new Specialite("Gastrologie", 11);
	Specialite* specialite3 = new Specialite("Sport", 7);
	Specialite* specialite4 = new Specialite("Podologie", 8);
	Specialite* specialite5 = new Specialite("Pediatrie", 9);

	//9-  Creez un objet du type Medecin à l'aide du constructeur par défaut
	Medecin medecin;
	//10- Modifiez le nom, les horaires et la specialite de ce dernier
	medecin.modifierHoraires(10);
	medecin.modifierNom("House");
	medecin.modifierSpecialite(specialite);
	//11- Creez 5 autres objets du type Medecin à l'aide du constructeur par paramètre avec des valeurs de votre choix
	Medecin medecin1("Sherlock", 5, specialite1);
	Medecin medecin2("Holmes", 6, specialite2);
	Medecin medecin3("Kyle", 7, specialite3);
	Medecin medecin4("Jean", 8, specialite4);
	Medecin medecin5("Jules", 9, specialite5);
	
	//13- Ajoutez les 6 objets du type Medecin à tableauMedecins de l'objet Personnel déjà créé
	
	personnel.ajouterMedecin(medecin);
	personnel.ajouterMedecin(medecin1);
	personnel.ajouterMedecin(medecin2);
	personnel.ajouterMedecin(medecin3);
	personnel.ajouterMedecin(medecin4);
	personnel.ajouterMedecin(medecin5);

	//14- Affichez la liste des medecins 
	personnel.afficherMedecins();
	//15- Affichez la liste des infirmiers
	cout << endl;
	personnel.afficherInfirmiers();
	cout << endl;

	delete specialite;
	delete specialite1;
	delete specialite2;
	delete specialite3;
	delete specialite4;
	delete specialite5;

	return 0;
}
