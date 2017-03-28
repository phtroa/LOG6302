
/**************************************************
* Titre: Travail pratique #3 - Main.cpp
* Date: 
* Auteur:
**************************************************/

#include "Piece.h"
#include "Roi.h"
#include "Tour.h"
#include "Pion.h"
#include "Echiquier.h"

#include <string.h>
#include <iostream>

using namespace std;

int main()
{
	//1-  Creez un objet de type Roi à l'aide du constructeur par défaut.
	Roi roi1 = Roi();

	//2- Donnez l'id D1 au roi défini dans l'étape 1
	roi1.modifierId("D1");

	//3-  Définissez la position (3,0) pour le roi défini dans l'étape 1
	roi1.modifierPositionX(3);
	roi1.modifierPositionY(0);

	//4-  Creez un objet de type Roi Noir à la position (3,7) ayant comme id D8.
	Roi roi2 = Roi("D8","noir",7,3);

	//5-  Creez les huit pions blancs avec les coordonnées (i,1) i : 0-->7 et les id A2-->H2
	Pion pionB1 = Pion("A2", "blanc", 0, 1);
	Pion pionB2 = Pion("B2", "blanc", 1, 1);
	Pion pionB3 = Pion("C2", "blanc", 2, 1);
	Pion pionB4 = Pion("D2", "blanc", 3, 1);
	Pion pionB5 = Pion("E2", "blanc", 4, 1);
	Pion pionB6 = Pion("F2", "blanc", 5, 1);
	Pion pionB7 = Pion("G2", "blanc", 6, 1);
	Pion pionB8 = Pion("H2", "blanc", 7, 1);

	//6-  Creez les huit pions noirs avec les coordonnées (i,6) i : 0-->7 et les id A7-->H7
	Pion pionN1 = Pion("A7", "noir", 0, 6);
	Pion pionN2 = Pion("B7", "noir", 1, 6);
	Pion pionN3 = Pion("C7", "noir", 2, 6);
	Pion pionN4 = Pion("D7", "noir", 3, 6);
	Pion pionN5 = Pion("E7", "noir", 4, 6);
	Pion pionN6 = Pion("F7", "noir", 5, 6);
	Pion pionN7 = Pion("G7", "noir", 6, 6);
	Pion pionN8 = Pion("H7", "noir", 7, 6);

	//7-  Creez les deux tours blanches d'id "A1" et "H1" dans les positions respectives (0,0) et (7,0)
	Tour tourB1 = Tour("A1", "blanc", 0, 0);
	Tour tourB2 = Tour("H1", "blanc", 7, 0);

	//8-  Creez les deux tours noires  d'id "A8" et "H8" dans les positions respectives (0,7) et (7,7)
	Tour tourN1 = Tour("A8", "noir", 0, 7);
	Tour tourN2 = Tour("H8", "noir", 7, 7);
	
	//9-  Creez un Echiquier
	Echiquier unEchiquier=Echiquier();

	//10- Ajoutez toutes les pièces précidament définies à l'echiquier
	unEchiquier.ajouterRoi(roi1,0);
	unEchiquier.ajouterRoi(roi2,1);

	unEchiquier.ajouterPion(pionB1);
	unEchiquier.ajouterPion(pionB2);
	unEchiquier.ajouterPion(pionB3);
	unEchiquier.ajouterPion(pionB4);
	unEchiquier.ajouterPion(pionB5);
	unEchiquier.ajouterPion(pionB6);
	unEchiquier.ajouterPion(pionB7);
	unEchiquier.ajouterPion(pionB8);

	unEchiquier.ajouterPion(pionN1);
	unEchiquier.ajouterPion(pionN2);
	unEchiquier.ajouterPion(pionN3);
	unEchiquier.ajouterPion(pionN4);
	unEchiquier.ajouterPion(pionN5);
	unEchiquier.ajouterPion(pionN6);
	unEchiquier.ajouterPion(pionN7);
	unEchiquier.ajouterPion(pionN8);

	unEchiquier.ajouterTour(tourB1);
	unEchiquier.ajouterTour(tourB2);
	unEchiquier.ajouterTour(tourN1);
	unEchiquier.ajouterTour(tourN2);

	//11-  Deplacer la piece d'id A2 à la position (0,2)  --Deplacement de Pion
	unEchiquier.deplacerPiece("A2", 0, 2);

	//12-  Deplacer le piece d'id H7 à la position (7,4)  --Deplacement du Pion
	unEchiquier.deplacerPiece("H7", 7, 4);

	//13-  Deplacer la piece d'id A2 à la position (0,4)  --Deplacement du Pion
	unEchiquier.deplacerPiece("A2", 0, 4);

	//14-  Deplacer la piece d'id H8 à la position (7,6)  --Deplacement de la Tour
	unEchiquier.deplacerPiece("H8", 7, 6);

	//15-  Deplacer la piece d'id H8 à la position (7,6)  --Deplacement de la Tour
	unEchiquier.deplacerPiece("H8", 7, 8);

	//16-  Enlever la piece d'id 
	unEchiquier.enleverPion("A2");

	system("pause");

	return 0;
}

