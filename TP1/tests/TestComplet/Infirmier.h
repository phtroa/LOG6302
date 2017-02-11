#ifndef INFIRMIER_H
#define INFIRMIER_H

#include <string>

class Infirmier
{
public:
	Infirmier();
	Infirmier(const std::string& nom, const std::string& prenom, unsigned int nbChambre);
	~Infirmier();

	std::string obtenirNom() const;
	std::string obtenirPrenom() const;
	unsigned int obtenirNbChambre() const;

	void modifierNom(const std::string& nom);
	void modifierPrenom(const std::string& prenom);
	void modifierNbChambre(unsigned int nbChambre);

	void afficherInformation() const;

private:
	std::string nom_;
	std::string prenom_;
	unsigned int nbChambre_;
};

#endif
