#pragma once
#include "Carc.h"
#include "Cexception.h"

using namespace std;

class CSommet
{
	protected:
		int eSOMNumero;

		CArc** SOMRelies;
		int eSOMArcNombre;

		int eSOMCouleurNumero;
	
	public:
		CSommet();
		~CSommet();
		CSommet(CSommet &sommet);

		void SOMSetSOMNumero(int eNum);
		void SOMSetSOMArcNombre(int eNum);
		void SOMSetSOMColourNumero(int eNum);
	
		int SOMLireSOMNumero();
		int SOMLireSOMArcNombre();
		int SOMLireeSOMColourNumero();

		CArc** SOMLireSOMRelies();
		CArc& SOMLirSOMReliesElement(int ePos);
};