#ifndef INFIRMIER_H
#define INFIRMIER_H

class Infirmier
{
public:
	char obtenirNom() const;


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
