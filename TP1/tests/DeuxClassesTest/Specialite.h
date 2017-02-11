#ifndef SPECIALITE_H
#define SPECIALITE_H

class Specialite
{
public:
	Specialite();
	~Specialite();

	Specialite(char domaine, unsigned int niveau);

	std::string obtenirDomaine() const;
	unsigned int obtenirNiveau() const;

	void modifierDomaine(char domaine);
	void modifierNiveau(unsigned int niveau);

	void afficherInformation() const;

private:
	char domaine_;
	unsigned int niveau_;
};

#endif
