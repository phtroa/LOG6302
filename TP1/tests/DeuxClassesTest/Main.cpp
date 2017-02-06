/**************************************************
 * Titre: Travail pratique #1 - Main.cpp
 * Date: 25 aout 2012
 * Auteur: 
**************************************************/

#include "Infirmier.h"
#include "Specialite.h"

int main()
{
	//1-  Creez un objet du type Infirmier à l'aide du constructeur par défaut
	Infirmier infirmier;
	//2-  Modifiez le nom, le prenom et le nbChambre de cet objet à l'aide des méthodes de modification
	infirmier.modifierNom('t');
	infirmier.modifierPrenom('e');
	infirmier.modifierNbChambre(10);
	//3-   constructeur par paramètre
	Infirmier infirmier1('s', 't', 2);

	//test Specialite
	Specialite specialite;

	return 0;
}
