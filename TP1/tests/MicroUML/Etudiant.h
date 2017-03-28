#pragma once

#include "Homme.h"

class Etudiant : public Homme
{
	private:
		int matricule;
	public:
		int getMatricule();
};
