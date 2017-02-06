#ifndef SPECIALITE_H
#define SPECIALITE_H

#include <string>

class Specialite
{
public:
	Specialite();
	~Specialite();

	Specialite(const std::string& domaine, unsigned int niveau);

	std::string obtenirDomaine() const;
	unsigned int obtenirNiveau() const;

	void modifierDomaine(const std::string& domaine);
	void modifierNiveau(unsigned int niveau);

	void afficherInformation() const;

private:
	std::string domaine_;
	unsigned int niveau_;
};

#endif
