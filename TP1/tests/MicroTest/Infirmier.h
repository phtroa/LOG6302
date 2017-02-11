#ifndef INFIRMIER_H
#define INFIRMIER_H

class Infirmier
{
public:
	Infirmier();
	Infirmier(const char nom, const char prenom, unsigned int nbChambre);
	~Infirmier();

	char obtenirNom() const;
	char obtenirPrenom() const;
	unsigned int obtenirNbChambre() const;

	void modifierNom(const char nom);
	void modifierPrenom(const char prenom);
	void modifierNbChambre(unsigned int nbChambre);

	void afficherInformation() const;

	void afficherInformationbis() const
	{
		int tmp = 0;
		for (int i = 0; i < nbChambre_/2; i++)
		{
			tmp += tmp + 1;
		}

		/*int tmp2 = 0;
		for (int i = 0; i < nbChambre_/2; i++)
		{
			tmp2 += tmp + 1;
		}*/
	}

private:
	char nom_;
	char prenom_;
	unsigned int nbChambre_;
};

#endif
