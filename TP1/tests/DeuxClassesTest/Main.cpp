/**************************************************
 * Titre: Travail pratique #1 - Main.cpp
 * Date: 25 aout 2012
 * Auteur: 
**************************************************/

#include "Infirmier.h"
#include "Specialite.h"

int main()
{
	//1-  Creez un objet du type Infirmier � l'aide du constructeur par d�faut
	Infirmier infirmier;
	//2-  Modifiez le nom, le prenom et le nbChambre de cet objet � l'aide des m�thodes de modification
	infirmier.modifierNom('t');
	infirmier.modifierPrenom('e');
	infirmier.modifierNbChambre(10);
	//3-   constructeur par param�tre
	Infirmier infirmier1('s', 't', 2);

	//test Specialite
	Specialite specialite;

	return 0;
}
